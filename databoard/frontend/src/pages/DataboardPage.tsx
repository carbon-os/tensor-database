import { useState, useCallback, useRef, useEffect } from 'react'
import Sidebar from '../components/Sidebar'
import TabBar from '../components/TabBar'
import QueryEditor from '../components/QueryEditor'
import ResultsPanel from '../components/ResultsPanel'
import '../components/Dashboard.css'
import type { QueryTab, QueryResult } from '../types'
import { SAMPLE_DBS, SAMPLE_RESULTS } from '../data/sample'

const SIDEBAR_MIN = 160
const SIDEBAR_MAX = 480
const EDITOR_MIN  = 80
const EDITOR_MAX  = 600

let tabCounter = 1

function makeTab(n: number, title?: string): QueryTab {
  return {
    id:     `tab-${n}`,
    title:  title ?? `Query ${n}`,
    query:  'select {\n  AlbumId,\n  Title,\n  ArtistId\n}\nfrom "store/albums" as a: Album\nlimit 50',
    result: null,
    status: 'idle',
  }
}

interface Props {
  onRunningChange: (v: boolean) => void
  registerRun:     (fn: () => void) => void
}

export default function DataboardPage({ onRunningChange, registerRun }: Props) {
  const [tabs, setTabs]                 = useState<QueryTab[]>([makeTab(1, 'Query 1')])
  const [activeTabId, setActiveTabId]   = useState('tab-1')
  const [sidebarWidth, setSidebarWidth] = useState(220)
  const [editorHeight, setEditorHeight] = useState(260)

  const activeTab       = tabs.find(t => t.id === activeTabId) ?? tabs[0]
  const dividerLineRef  = useRef<HTMLDivElement>(null)
  const hDividerLineRef = useRef<HTMLDivElement>(null)

  // ── Tab helpers ─────────────────────────────────────────────────────────────
  const patchTab = useCallback((id: string, patch: Partial<QueryTab>) => {
    setTabs(prev => prev.map(t => t.id === id ? { ...t, ...patch } : t))
  }, [])

  const handleAddTab = () => {
    const n   = ++tabCounter
    const tab = makeTab(n)
    setTabs(prev => [...prev, tab])
    setActiveTabId(tab.id)
  }

  const handleCloseTab = (id: string) => {
    if (tabs.length === 1) return
    const idx      = tabs.findIndex(t => t.id === id)
    const fallback = tabs[idx - 1] ?? tabs[idx + 1]
    setTabs(prev => prev.filter(t => t.id !== id))
    if (activeTabId === id && fallback) setActiveTabId(fallback.id)
  }

  const handleReorder = (reordered: QueryTab[]) => {
    setTabs(reordered)
  }

  // ── Query execution ─────────────────────────────────────────────────────────
  const handleRun = useCallback(() => {
    const id = activeTabId
    patchTab(id, { status: 'running', result: null })
    onRunningChange(true)

    const delay = 350 + Math.random() * 450
    setTimeout(() => {
      const match =
        activeTab.query.match(/from\s+"[^"]*\/([^"]+)"/i) ??
        activeTab.query.match(/from\s+(\w+)/i)
      const key             = match?.[1]?.toLowerCase() ?? ''
      const result: QueryResult = SAMPLE_RESULTS[key] ?? SAMPLE_RESULTS.default
      patchTab(id, { status: 'done', result })
      onRunningChange(false)
    }, delay)
  }, [activeTabId, activeTab.query, patchTab, onRunningChange])

  useEffect(() => {
    registerRun(handleRun)
  }, [handleRun, registerRun])

  const handleTableClick = (tableName: string) => {
    patchTab(activeTabId, {
      query:  `select {\n  *\n}\nfrom "store/${tableName}" as t: ${tableName}\nlimit 100`,
      title:  tableName,
      result: null,
      status: 'idle',
    })
  }

  // ── Sidebar resize ───────────────────────────────────────────────────────────
  const isSidebarDragging = useRef(false)

  const handleDividerMouseDown = useCallback((e: React.MouseEvent) => {
    e.preventDefault()
    isSidebarDragging.current = true

    const startX     = e.clientX
    const startWidth = sidebarWidth

    if (dividerLineRef.current)
      dividerLineRef.current.style.background = '#a0a0a0'

    const onMouseMove = (ev: MouseEvent) => {
      if (!isSidebarDragging.current) return
      const next = Math.min(SIDEBAR_MAX, Math.max(SIDEBAR_MIN, startWidth + ev.clientX - startX))
      setSidebarWidth(next)
    }

    const onMouseUp = () => {
      isSidebarDragging.current          = false
      document.body.style.cursor         = ''
      document.body.style.userSelect     = ''
      if (dividerLineRef.current)
        dividerLineRef.current.style.background = '#e2e2e2'
      document.removeEventListener('mousemove', onMouseMove)
      document.removeEventListener('mouseup',   onMouseUp)
    }

    document.addEventListener('mousemove', onMouseMove)
    document.addEventListener('mouseup',   onMouseUp)
    document.body.style.cursor     = 'col-resize'
    document.body.style.userSelect = 'none'
  }, [sidebarWidth])

  // ── Editor / results resize ──────────────────────────────────────────────────
  const isEditorDragging = useRef(false)

  const handleEditorDividerMouseDown = useCallback((e: React.MouseEvent) => {
    e.preventDefault()
    isEditorDragging.current = true

    const startY      = e.clientY
    const startHeight = editorHeight

    if (hDividerLineRef.current)
      hDividerLineRef.current.style.background = '#a0a0a0'

    const onMouseMove = (ev: MouseEvent) => {
      if (!isEditorDragging.current) return
      const next = Math.min(EDITOR_MAX, Math.max(EDITOR_MIN, startHeight + ev.clientY - startY))
      setEditorHeight(next)
    }

    const onMouseUp = () => {
      isEditorDragging.current           = false
      document.body.style.cursor         = ''
      document.body.style.userSelect     = ''
      if (hDividerLineRef.current)
        hDividerLineRef.current.style.background = '#e2e2e2'
      document.removeEventListener('mousemove', onMouseMove)
      document.removeEventListener('mouseup',   onMouseUp)
    }

    document.addEventListener('mousemove', onMouseMove)
    document.addEventListener('mouseup',   onMouseUp)
    document.body.style.cursor     = 'row-resize'
    document.body.style.userSelect = 'none'
  }, [editorHeight])

  // ── Render ──────────────────────────────────────────────────────────────────
  return (
    <div style={{
      display:    'flex',
      height:     '100%',
      overflow:   'hidden',
      background: 'var(--color-background-primary)',
    }}>

      {/* Sidebar — drag handle absolutely positioned on right edge */}
      <div style={{ width: sidebarWidth, flexShrink: 0, overflow: 'hidden', position: 'relative' }}>
        <Sidebar databases={SAMPLE_DBS} onTableClick={handleTableClick} />

        <div
          onMouseDown={handleDividerMouseDown}
          onMouseEnter={() => {
            if (dividerLineRef.current)
              dividerLineRef.current.style.background = '#c0c0c0'
          }}
          onMouseLeave={() => {
            if (!isSidebarDragging.current && dividerLineRef.current)
              dividerLineRef.current.style.background = '#e2e2e2'
          }}
          style={{
            position: 'absolute',
            top:      0,
            right:    -2,
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
      </div>

      {/* Main pane — flush with sidebar */}
      <div style={{
        flex:          1,
        display:       'flex',
        flexDirection: 'column',
        overflow:      'hidden',
        minWidth:      0,
      }}>
        <TabBar
          tabs={tabs}
          activeTabId={activeTabId}
          onSelect={setActiveTabId}
          onAdd={handleAddTab}
          onClose={handleCloseTab}
          onReorder={handleReorder}
        />

        <QueryEditor
          query={activeTab.query}
          status={activeTab.status}
          height={editorHeight}
          onChange={q => patchTab(activeTabId, { query: q })}
          onRun={handleRun}
        />

        {/* Editor / results drag handle */}
        <div
          onMouseDown={handleEditorDividerMouseDown}
          onMouseEnter={() => {
            if (hDividerLineRef.current)
              hDividerLineRef.current.style.background = '#c0c0c0'
          }}
          onMouseLeave={() => {
            if (!isEditorDragging.current && hDividerLineRef.current)
              hDividerLineRef.current.style.background = '#e2e2e2'
          }}
          style={{
            height:     '5px',
            flexShrink: 0,
            cursor:     'row-resize',
            position:   'relative',
            zIndex:     10,
          }}
        >
          <div
            ref={hDividerLineRef}
            style={{
              position:   'absolute',
              left:       0,
              right:      0,
              top:        '2px',
              height:     '1px',
              background: '#e2e2e2',
              transition: 'background 0.15s',
            }}
          />
        </div>

        <ResultsPanel result={activeTab.result} status={activeTab.status} />
      </div>

    </div>
  )
}