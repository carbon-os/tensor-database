import { useState } from 'react'
import { ChevronDown, Settings, Search, Play, Loader2, MessageSquare } from 'lucide-react'
import logo from '../assets/logo.png'

const PROJECTS = [
  { id: 'tensor-prod',    name: 'tensor-prod'    },
  { id: 'tensor-staging', name: 'tensor-staging' },
  { id: 'rivers-db',      name: 'rivers-db'      },
  { id: 'chinook-demo',   name: 'chinook-demo'   },
]

interface Props {
  onRun:         () => void
  isRunning:     boolean
  onChatToggle:  () => void
  isChatOpen:    boolean
}

export default function TopBar({ onRun, isRunning, onChatToggle, isChatOpen }: Props) {
  const [activeProject, setActiveProject] = useState(PROJECTS[0])
  const [dropdownOpen, setDropdownOpen]   = useState(false)

  return (
    <div style={{
      height:              '48px',
      background:          'transparent',
      borderBottom:        '1px solid #e2e2e2',
      display:             'grid',
      gridTemplateColumns: '1fr auto 1fr',
      alignItems:          'center',
      padding:             '0 12px',
      flexShrink:          0,
      position:            'relative',
      zIndex:              100,
    }}>

      {/* Left — logo + project selector */}
      <div style={{ display: 'flex', alignItems: 'center', gap: '4px' }}>
        <div style={{
          display:     'flex',
          alignItems:  'center',
          gap:         '8px',
          marginRight: '8px',
          userSelect:  'none',
        }}>
          <img src={logo} alt="TensorDB" style={{ height: '30px', width: 'auto', display: 'block' }} />
          <span style={{ fontSize: '16px', fontWeight: 500, color: 'var(--color-text-primary)', letterSpacing: '0.01em' }}>
            TensorDB
          </span>
        </div>

        <div style={{ position: 'relative' }}>
          <button
            onClick={() => setDropdownOpen(o => !o)}
            style={{
              display:      'flex',
              alignItems:   'center',
              gap:          '5px',
              padding:      '4px 9px',
              background:   dropdownOpen ? 'var(--color-background-secondary)' : 'transparent',
              border:       '0.5px solid var(--color-border-secondary)',
              borderRadius: 'var(--border-radius-md)',
              cursor:       'pointer',
              color:        'var(--color-text-primary)',
              fontSize:     '13px',
              fontWeight:   400,
              transition:   'background 0.15s',
              whiteSpace:   'nowrap',
            }}
            onMouseEnter={e => (e.currentTarget.style.background = 'var(--color-background-secondary)')}
            onMouseLeave={e => (e.currentTarget.style.background = dropdownOpen ? 'var(--color-background-secondary)' : 'transparent')}
          >
            {activeProject.name}
            <ChevronDown size={12} style={{ color: 'var(--color-text-tertiary)', marginLeft: '1px' }} />
          </button>

          {dropdownOpen && (
            <>
              <div style={{ position: 'fixed', inset: 0, zIndex: 99 }} onClick={() => setDropdownOpen(false)} />
              <div style={{
                position:     'absolute',
                top:          'calc(100% + 6px)',
                left:         0,
                minWidth:     '200px',
                background:   'var(--color-background-primary)',
                borderRadius: 'var(--border-radius-md)',
                boxShadow:    '0 4px 16px rgba(0,0,0,0.12)',
                zIndex:       200,
                overflow:     'hidden',
                border:       '0.5px solid var(--color-border-tertiary)',
              }}>
                <div style={{
                  padding:       '8px 12px 6px',
                  fontSize:      '11px',
                  fontWeight:    500,
                  color:         'var(--color-text-tertiary)',
                  letterSpacing: '0.06em',
                  textTransform: 'uppercase',
                  borderBottom:  '0.5px solid var(--color-border-tertiary)',
                }}>
                  Projects
                </div>
                {PROJECTS.map(p => (
                  <button
                    key={p.id}
                    onClick={() => { setActiveProject(p); setDropdownOpen(false) }}
                    style={{
                      display:    'flex',
                      alignItems: 'center',
                      gap:        '8px',
                      width:      '100%',
                      padding:    '8px 12px',
                      background: p.id === activeProject.id ? 'var(--color-background-secondary)' : 'transparent',
                      border:     'none',
                      cursor:     'pointer',
                      fontSize:   '13px',
                      color:      'var(--color-text-primary)',
                      textAlign:  'left',
                      fontWeight: p.id === activeProject.id ? 500 : 400,
                      transition: 'background 0.1s',
                    }}
                    onMouseEnter={e => { if (p.id !== activeProject.id) e.currentTarget.style.background = 'var(--color-background-secondary)' }}
                    onMouseLeave={e => { if (p.id !== activeProject.id) e.currentTarget.style.background = 'transparent' }}
                  >
                    <span style={{
                      width:        '6px',
                      height:       '6px',
                      borderRadius: '50%',
                      background:   p.id === activeProject.id ? 'var(--color-text-primary)' : 'var(--color-border-secondary)',
                      flexShrink:   0,
                    }} />
                    {p.name}
                    {p.id === activeProject.id && (
                      <span style={{ marginLeft: 'auto', fontSize: '13px', color: 'var(--color-text-secondary)' }}>✓</span>
                    )}
                  </button>
                ))}
              </div>
            </>
          )}
        </div>
      </div>

      {/* Center — search */}
      <div
        style={{
          width:        '520px',
          display:      'flex',
          alignItems:   'center',
          gap:          '7px',
          background:   'transparent',
          border:       '1px solid #e2e2e2',
          borderRadius: '8px',
          padding:      '0 14px',
          height:       '32px',
          transition:   'border-color 0.15s, background 0.15s',
        }}
        onFocusCapture={e => { e.currentTarget.style.background = '#fff'; e.currentTarget.style.borderColor = '#c0c0c0' }}
        onBlurCapture={e =>  { e.currentTarget.style.background = 'transparent'; e.currentTarget.style.borderColor = '#e2e2e2' }}
      >
        <Search size={13} style={{ color: '#9aa0a6', flexShrink: 0 }} />
        <input
          placeholder="Search tables, queries…"
          style={{ background: 'transparent', border: 'none', outline: 'none', color: 'var(--color-text-primary)', fontSize: '13px', width: '100%' }}
        />
      </div>

      {/* Right — run + icons */}
      <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'flex-end', gap: '6px' }}>
        <button
          onClick={onRun}
          disabled={isRunning}
          style={{
            display:      'flex',
            alignItems:   'center',
            gap:          '6px',
            padding:      '5px 14px',
            background:   'rgb(235 235 235)',
            color:        isRunning ? 'rgba(0,0,0,0.35)' : 'rgb(0,0,0)',
            border:       'none',
            borderRadius: '35px',
            cursor:       isRunning ? 'not-allowed' : 'pointer',
            fontSize:     '13px',
            fontWeight:   500,
            transition:   'background 0.15s',
          }}
          onMouseEnter={e => { if (!isRunning) e.currentTarget.style.background = 'rgb(220 220 220)' }}
          onMouseLeave={e => { if (!isRunning) e.currentTarget.style.background = 'rgb(235 235 235)' }}
        >
          {isRunning
            ? <Loader2 size={13} style={{ animation: 'tabSpin 0.8s linear infinite' }} />
            : <Play size={13} />
          }
          {isRunning ? 'Running…' : 'Run'}
        </button>

        <TopBarIcon title="AI Assistant" onClick={onChatToggle} active={isChatOpen}>
          <MessageSquare size={15} />
        </TopBarIcon>
        <TopBarIcon title="Settings">
          <Settings size={15} />
        </TopBarIcon>
      </div>
    </div>
  )
}

function TopBarIcon({
  children, title, onClick, active,
}: {
  children: React.ReactNode
  title:    string
  onClick?: () => void
  active?:  boolean
}) {
  return (
    <button
      title={title}
      onClick={onClick}
      style={{
        background:     active ? 'var(--color-background-secondary)' : 'none',
        border:         'none',
        cursor:         'pointer',
        color:          active ? 'var(--color-text-primary)' : 'var(--color-text-secondary)',
        width:          '32px',
        height:         '32px',
        borderRadius:   '50%',
        display:        'flex',
        alignItems:     'center',
        justifyContent: 'center',
        flexShrink:     0,
        transition:     'background 0.15s, color 0.15s',
      }}
      onMouseEnter={e => { e.currentTarget.style.background = 'var(--color-background-secondary)'; e.currentTarget.style.color = 'var(--color-text-primary)' }}
      onMouseLeave={e => { e.currentTarget.style.background = active ? 'var(--color-background-secondary)' : 'none'; e.currentTarget.style.color = active ? 'var(--color-text-primary)' : 'var(--color-text-secondary)' }}
    >
      {children}
    </button>
  )
}