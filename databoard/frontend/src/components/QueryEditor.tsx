import { useRef, useEffect } from 'react'
import MonacoEditor, { type BeforeMount, type OnMount } from '@monaco-editor/react'
import type { QueryTab } from '../types'
import { TQL_LANGUAGE_ID, registerTqlLanguage } from '../lib/tqlLanguage'

interface Props {
  query:    string
  status:   QueryTab['status']
  height:   number
  onChange: (q: string) => void
  onRun:    () => void
}

const EDITOR_OPTIONS = {
  minimap:                    { enabled: false },
  fontSize:                   13,
  lineHeight:                 21,
  fontFamily:                 'ui-monospace, "Cascadia Code", "Fira Code", Menlo, monospace',
  fontLigatures:              true,
  scrollBeyondLastLine:       false,
  wordWrap:                   'on' as const,
  renderLineHighlight:        'none' as const,
  overviewRulerLanes:         0,
  hideCursorInOverviewRuler:  true,
  scrollbar:                  { vertical: 'auto' as const, horizontal: 'hidden' as const, verticalScrollbarSize: 4 },
  padding:                    { top: 12, bottom: 12 },
  lineNumbers:                'on' as const,
  glyphMargin:                false,
  folding:                    false,
  contextmenu:                false,
  smoothScrolling:            true,
  cursorBlinking:             'smooth' as const,
  cursorSmoothCaretAnimation: 'on' as const,
  tabSize:                    2,
}

export default function QueryEditor({ query, status, height, onChange, onRun }: Props) {
  const onRunRef = useRef(onRun)
  useEffect(() => { onRunRef.current = onRun }, [onRun])

  const handleBeforeMount: BeforeMount = (monaco) => {
    registerTqlLanguage(monaco)
  }

  const handleMount: OnMount = (editor, monaco) => {
    editor.addCommand(
      monaco.KeyMod.CtrlCmd | monaco.KeyCode.Enter,
      () => onRunRef.current(),
    )
    editor.focus()
  }

  return (
    <div style={{
      height:     `${height}px`,
      flexShrink: 0,
    }}>
      <MonacoEditor
        height="100%"
        language={TQL_LANGUAGE_ID}
        value={query}
        theme="tql-light"
        beforeMount={handleBeforeMount}
        onMount={handleMount}
        onChange={v => onChange(v ?? '')}
        options={EDITOR_OPTIONS}
      />
    </div>
  )
}