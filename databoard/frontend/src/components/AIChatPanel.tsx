import { useState, useRef, useEffect } from 'react'
import { X, ArrowUp } from 'lucide-react'
import logo from '../assets/logo.png'

interface Message {
  id:      string
  role:    'user' | 'assistant'
  content: string
}

const SUGGESTIONS = [
  'How do I write a join in TQL?',
  'What is the syntax for upsert?',
  'How do I use the embed() function?',
  'How do I group by and aggregate?',
]

const MOCK_RESPONSES: Record<string, string> = {
  default: `I can help you with TQL queries and debugging. Try asking about specific syntax, functions, or paste an error you're seeing.`,
  join: `To write a join in TQL:

\`\`\`
from "store/orders" as o: Order
join "store/customers" as c: Customer
  on o.CustomerId == c.CustomerId
select {
  orderId: o.OrderId,
  customer: c.Name,
  total: o.Total
}
\`\`\`

Use \`left join\` for a left outer join — unmatched rows will have null values on the right side.`,

  upsert: `The upsert syntax in TQL:

\`\`\`
upsert into "store/customers" as c: Customer
conflict on CustomerId
values {
  CustomerId: 42,
  Name: "Jane Doe",
  Email: "jane@example.com"
}
conflict set {
  Name: "Jane Doe",
  Email: "jane@example.com"
}
\`\`\`

The \`conflict on\` field must be a unique key. Fields in \`conflict set\` are updated on collision.`,

  embed: `\`embed()\` generates a vector from a string query for similarity search:

\`\`\`
from "store/products" as p: Product
order by p.embedding <-> embed("wireless headphones") asc
limit 10
select {
  name: p.Name,
  price: p.Price
}
\`\`\`

The \`<->\` operator is only valid inside \`order by\`. The dimension of \`embed()\` must match the field's declared \`vector(n)\` type.`,

  group: `Grouping and aggregation in TQL:

\`\`\`
from "store/invoices" as i: Invoice
group by i.CustomerId
select {
  customerId: i.CustomerId,
  totalSpent:  sum(i.Total),
  orderCount:  count(*),
  avgOrder:    avg(i.Total)
}
having sum(i.Total) > 100
\`\`\`

Aggregate functions are only valid inside a pipeline that has a \`group by\` clause.`,
}

function getMockResponse(input: string): string {
  const lower = input.toLowerCase()
  if (lower.includes('join'))                                   return MOCK_RESPONSES.join
  if (lower.includes('upsert'))                                 return MOCK_RESPONSES.upsert
  if (lower.includes('embed') || lower.includes('vector'))      return MOCK_RESPONSES.embed
  if (lower.includes('group') || lower.includes('aggregate') || lower.includes('sum') || lower.includes('count')) return MOCK_RESPONSES.group
  return MOCK_RESPONSES.default
}

interface Props {
  onClose:            () => void
  width:              number
  onDividerMouseDown: (e: React.MouseEvent) => void
  dividerLineRef:     React.RefObject<HTMLDivElement>
  isDragging:         React.MutableRefObject<boolean>
}

export default function AIChatPanel({ onClose, width, onDividerMouseDown, dividerLineRef, isDragging }: Props) {
  const [messages, setMessages] = useState<Message[]>([])
  const [input, setInput]       = useState('')
  const [isTyping, setIsTyping] = useState(false)
  const bottomRef               = useRef<HTMLDivElement>(null)
  const inputRef                = useRef<HTMLTextAreaElement>(null)

  useEffect(() => {
    bottomRef.current?.scrollIntoView({ behavior: 'smooth' })
  }, [messages, isTyping])

  useEffect(() => {
    inputRef.current?.focus()
  }, [])

  const sendMessage = (text: string) => {
    if (!text.trim() || isTyping) return
    const userMsg: Message = { id: Date.now().toString(), role: 'user', content: text.trim() }
    setMessages(prev => [...prev, userMsg])
    setInput('')
    setIsTyping(true)
    setTimeout(() => {
      const reply: Message = {
        id:      (Date.now() + 1).toString(),
        role:    'assistant',
        content: getMockResponse(text),
      }
      setMessages(prev => [...prev, reply])
      setIsTyping(false)
    }, 600 + Math.random() * 400)
  }

  const handleKeyDown = (e: React.KeyboardEvent<HTMLTextAreaElement>) => {
    if (e.key === 'Enter' && !e.shiftKey) {
      e.preventDefault()
      sendMessage(input)
    }
  }

  return (
    <div style={{
      width:         `${width}px`,
      flexShrink:    0,
      display:       'flex',
      flexDirection: 'column',
      background:    '#ffffff',
      color:         '#1a1a1a',
      overflow:      'hidden',
      position:      'relative',
    }}>

      {/* Drag handle */}
      <div
        onMouseDown={onDividerMouseDown}
        onMouseEnter={() => {
          if (dividerLineRef.current)
            dividerLineRef.current.style.background = '#c0c0c0'
        }}
        onMouseLeave={() => {
          if (!isDragging.current && dividerLineRef.current)
            dividerLineRef.current.style.background = '#e2e2e2'
        }}
        style={{
          position: 'absolute',
          top:      0,
          left:     -2,
          bottom:   0,
          width:    '5px',
          cursor:   'col-resize',
          zIndex:   10,
        }}
      >
        <div
          ref={dividerLineRef}
          style={{
            position:   'absolute',
            top:        0,
            bottom:     0,
            left:       '2px',
            width:      '1px',
            background: '#e2e2e2',
            transition: 'background 0.15s',
          }}
        />
      </div>

      {/* Header */}
      <div style={{
        display:        'flex',
        alignItems:     'center',
        justifyContent: 'space-between',
        padding:        '0 12px',
        height:         '48px',
        flexShrink:     0,
      }}>
        <span style={{ fontSize: '13px', fontWeight: 500, color: '#1a1a1a' }}>TQL Assistant</span>
        <button
          onClick={onClose}
          style={{
            background: 'none', border: 'none', cursor: 'pointer',
            color: '#9aa0a6', display: 'flex', alignItems: 'center',
            justifyContent: 'center', width: '26px', height: '26px',
            borderRadius: '4px', transition: 'background 0.15s, color 0.15s',
          }}
          onMouseEnter={e => { e.currentTarget.style.background = '#f1f3f4'; e.currentTarget.style.color = '#1a1a1a' }}
          onMouseLeave={e => { e.currentTarget.style.background = 'none';    e.currentTarget.style.color = '#9aa0a6' }}
        >
          <X size={14} />
        </button>
      </div>

      {/* Messages */}
      <div style={{
        flex:          1,
        overflowY:     'auto',
        padding:       '16px 12px',
        display:       'flex',
        flexDirection: 'column',
        gap:           '12px',
      }}>

        {messages.length === 0 && (
          <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', marginTop: '32px', gap: '12px' }}>
            <img
              src={logo}
              alt="TensorDB"
              style={{ height: '40px', width: 'auto', display: 'block' }}
            />
            <div style={{ textAlign: 'center' }}>
              <div style={{ fontSize: '13px', fontWeight: 500, color: '#1a1a1a', marginBottom: '4px' }}>Ask about your code</div>
              <div style={{ fontSize: '12px', color: '#9aa0a6' }}>AI responses may be inaccurate</div>
            </div>
            <div style={{ display: 'flex', flexDirection: 'column', gap: '6px', width: '100%', marginTop: '8px' }}>
              {SUGGESTIONS.map(s => (
                <button
                  key={s}
                  onClick={() => sendMessage(s)}
                  style={{
                    background:   '#f7f7f7',
                    border:       '1px solid #e2e2e2',
                    borderRadius: '6px',
                    padding:      '8px 10px',
                    cursor:       'pointer',
                    color:        '#6e6e6e',
                    fontSize:     '12px',
                    textAlign:    'left',
                    transition:   'background 0.15s, color 0.15s',
                  }}
                  onMouseEnter={e => { e.currentTarget.style.background = '#eeeeee'; e.currentTarget.style.color = '#1a1a1a' }}
                  onMouseLeave={e => { e.currentTarget.style.background = '#f7f7f7'; e.currentTarget.style.color = '#6e6e6e' }}
                >
                  {s}
                </button>
              ))}
            </div>
          </div>
        )}

        {messages.map(msg => (
          <div
            key={msg.id}
            style={{
              display:        'flex',
              justifyContent: msg.role === 'user' ? 'flex-end' : 'flex-start',
            }}
          >
            {msg.role === 'user' ? (
              <div style={{
                background:   '#f1f3f4',
                borderRadius: '14px 14px 3px 14px',
                padding:      '8px 12px',
                fontSize:     '13px',
                lineHeight:   '1.6',
                color:        '#1a1a1a',
                maxWidth:     '80%',
                wordBreak:    'break-word',
              }}>
                {msg.content}
              </div>
            ) : (
              <div style={{ flex: 1, fontSize: '13px', lineHeight: '1.6', color: '#1a1a1a' }}>
                {msg.content.split('```').map((part, i) =>
                  i % 2 === 1
                    ? (
                      <pre key={i} style={{
                        background:   '#f7f7f7',
                        border:       '1px solid #e2e2e2',
                        borderRadius: '6px',
                        padding:      '10px 12px',
                        fontSize:     '12px',
                        overflowX:    'auto',
                        margin:       '8px 0',
                        fontFamily:   'ui-monospace, "Cascadia Code", Menlo, monospace',
                        color:        '#a31515',
                        whiteSpace:   'pre-wrap',
                      }}>
                        {part.replace(/^\w+\n/, '')}
                      </pre>
                    )
                    : <span key={i}>{part}</span>
                )}
              </div>
            )}
          </div>
        ))}

        {isTyping && (
          <div style={{ display: 'flex', alignItems: 'center', gap: '4px', paddingTop: '2px' }}>
            {[0, 1, 2].map(i => (
              <div key={i} style={{
                width:        '5px',
                height:       '5px',
                borderRadius: '50%',
                background:   '#1a73e8',
                animation:    `chatPulse 1.2s ease-in-out ${i * 0.2}s infinite`,
              }} />
            ))}
          </div>
        )}

        <div ref={bottomRef} />
      </div>

      {/* Input */}
      <div style={{ padding: '10px 12px', flexShrink: 0 }}>
        <div
          style={{
            display:      'flex',
            alignItems:   'flex-end',
            gap:          '8px',
            background:   '#f7f7f7',
            border:       '1px solid #e2e2e2',
            borderRadius: '12px',
            padding:      '8px 8px 8px 12px',
            transition:   'border-color 0.15s',
          }}
          onFocusCapture={e => (e.currentTarget.style.borderColor = '#1a73e8')}
          onBlurCapture={e  => (e.currentTarget.style.borderColor = '#e2e2e2')}
        >
          <textarea
            ref={inputRef}
            value={input}
            onChange={e => setInput(e.target.value)}
            onKeyDown={handleKeyDown}
            placeholder="Ask about TQL, errors, syntax…"
            rows={4}
            style={{
              flex:       1,
              background: 'transparent',
              border:     'none',
              outline:    'none',
              color:      '#1a1a1a',
              fontSize:   '13px',
              resize:     'none',
              lineHeight: '1.5',
              fontFamily: 'inherit',
              maxHeight:  '200px',
              overflowY:  'auto',
            }}
            onInput={e => {
              const el = e.currentTarget
              el.style.height = 'auto'
              el.style.height = `${el.scrollHeight}px`
            }}
          />
          <button
            onClick={() => sendMessage(input)}
            disabled={!input.trim() || isTyping}
            style={{
              background:     input.trim() && !isTyping ? '#1a73e8' : '#e2e2e2',
              border:         'none',
              borderRadius:   '8px',
              cursor:         input.trim() && !isTyping ? 'pointer' : 'not-allowed',
              color:          input.trim() && !isTyping ? '#fff' : '#9aa0a6',
              display:        'flex',
              alignItems:     'center',
              justifyContent: 'center',
              width:          '28px',
              height:         '28px',
              flexShrink:     0,
              transition:     'background 0.15s',
            }}
          >
            <ArrowUp size={14} />
          </button>
        </div>
        <div style={{ fontSize: '11px', color: '#b0b0b0', marginTop: '6px', textAlign: 'center' }}>
          Enter to send · Shift+Enter for new line
        </div>
      </div>

      <style>{`
        @keyframes chatPulse {
          0%, 100% { opacity: 0.3; transform: scale(0.8); }
          50%       { opacity: 1;   transform: scale(1.1); }
        }
      `}</style>
    </div>
  )
}