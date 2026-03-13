import { useState, useRef, useCallback } from 'react'
import { BrowserRouter, Routes, Route } from 'react-router-dom'
import DataboardPage from './pages/DataboardPage'
import TopBar from './components/TopBar'
import AIChatPanel from './components/AIChatPanel'
import type { Theme } from './types'
import './App.css'

const CHAT_MIN = 260
const CHAT_MAX = 600

export default function App() {
  const [theme]                     = useState<Theme>('light')
  const [isRunning, setIsRunning]   = useState(false)
  const [onRunFn, setOnRunFn]       = useState<(() => void) | null>(null)
  const [isChatOpen, setIsChatOpen] = useState(false)
  const [chatWidth, setChatWidth]   = useState(340)

  const registerRun = (fn: () => void) => setOnRunFn(() => fn)
  const handleRun   = () => { if (onRunFn) onRunFn() }

  const isChatDragging = useRef(false)
  const chatDividerRef = useRef<HTMLDivElement>(null)

  const handleChatDividerMouseDown = useCallback((e: React.MouseEvent) => {
    e.preventDefault()
    isChatDragging.current = true

    const startX     = e.clientX
    const startWidth = chatWidth

    if (chatDividerRef.current)
      chatDividerRef.current.style.background = '#a0a0a0'

    const onMouseMove = (ev: MouseEvent) => {
      if (!isChatDragging.current) return
      const next = Math.min(CHAT_MAX, Math.max(CHAT_MIN, startWidth - (ev.clientX - startX)))
      setChatWidth(next)
    }

    const onMouseUp = () => {
      isChatDragging.current         = false
      document.body.style.cursor     = ''
      document.body.style.userSelect = ''
      if (chatDividerRef.current)
        chatDividerRef.current.style.background = '#e2e2e2'
      document.removeEventListener('mousemove', onMouseMove)
      document.removeEventListener('mouseup',   onMouseUp)
    }

    document.addEventListener('mousemove', onMouseMove)
    document.addEventListener('mouseup',   onMouseUp)
    document.body.style.cursor     = 'col-resize'
    document.body.style.userSelect = 'none'
  }, [chatWidth])

  return (
    <BrowserRouter>
      <div className="app" data-theme={theme}>
        <TopBar
          onRun={handleRun}
          isRunning={isRunning}
          onChatToggle={() => setIsChatOpen(o => !o)}
          isChatOpen={isChatOpen}
        />
        <main className="app-content" style={{ display: 'flex', overflow: 'hidden' }}>

          <div style={{ flex: 1, overflow: 'hidden', minWidth: 0 }}>
            <Routes>
              <Route
                path="/"
                element={
                  <DataboardPage
                    onRunningChange={setIsRunning}
                    registerRun={registerRun}
                  />
                }
              />
            </Routes>
          </div>

          {isChatOpen && (
            <AIChatPanel
              onClose={() => setIsChatOpen(false)}
              width={chatWidth}
              onDividerMouseDown={handleChatDividerMouseDown}
              dividerLineRef={chatDividerRef}
              isDragging={isChatDragging}
            />
          )}

        </main>
      </div>
    </BrowserRouter>
  )
}