import {
  DndContext,
  closestCenter,
  PointerSensor,
  useSensor,
  useSensors,
  type DragEndEvent,
} from '@dnd-kit/core'
import {
  SortableContext,
  horizontalListSortingStrategy,
  useSortable,
  arrayMove,
} from '@dnd-kit/sortable'
import { CSS } from '@dnd-kit/utilities'
import { Plus, X, FileCode2, Loader2, FileX2 } from 'lucide-react'
import type { QueryTab } from '../types'

interface TabBarProps {
  tabs:        QueryTab[]
  activeTabId: string
  onSelect:    (id: string) => void
  onAdd:       () => void
  onClose:     (id: string) => void
  onReorder:   (tabs: QueryTab[]) => void
}

function TabIcon({ status, isActive }: { status: QueryTab['status']; isActive: boolean }) {
  if (status === 'running') {
    return (
      <Loader2
        size={13}
        style={{ flexShrink: 0, color: '#1a73e8', animation: 'tabSpin 0.8s linear infinite' }}
      />
    )
  }
  if (status === 'error') {
    return <FileX2 size={13} style={{ flexShrink: 0, color: '#d93025' }} />
  }
  return (
    <FileCode2
      size={13}
      style={{ flexShrink: 0, color: isActive ? '#1a73e8' : '#9aa0a6' }}
    />
  )
}

interface SortableTabProps {
  tab:      QueryTab
  isActive: boolean
  onSelect: () => void
  onClose:  () => void
}

const TAB_BAR_BG   = '#f7f7f7'
const ACTIVE_BG    = '#ffffff'
const INACTIVE_BG  = '#f7f7f7'
const INACTIVE_HOV = '#eeeeee'

function SortableTab({ tab, isActive, onSelect, onClose }: SortableTabProps) {
  const {
    attributes,
    listeners,
    setNodeRef,
    transform,
    transition,
    isDragging,
  } = useSortable({ id: tab.id })

  const style: React.CSSProperties = {
    transform:  CSS.Transform.toString(transform),
    transition: isDragging ? 'none' : (transition ?? undefined),
    zIndex:     isDragging ? 10 : undefined,
    opacity:    isDragging ? 0.5 : 1,
  }

  return (
    <div
      ref={setNodeRef}
      style={{
        ...style,
        display:    'flex',
        alignItems: 'stretch',
        flexShrink: 0,
        position:   'relative',
        cursor:     isDragging ? 'grabbing' : 'pointer',
      }}
    >
      <div
        onClick={onSelect}
        {...attributes}
        {...listeners}
        style={{
          display:      'flex',
          alignItems:   'center',
          gap:          '6px',
          padding:      '0 8px 0 12px',
          height:       '36px',
          fontSize:     '13px',
          color:        isActive ? '#1a1a1a' : '#6e6e6e',
          background:   isActive ? ACTIVE_BG : INACTIVE_BG,
          borderRight:  '1px solid #d8d8d8',
          borderTop:    isActive ? '1px solid #1a73e8' : '1px solid transparent',
          borderBottom: isActive ? `1px solid ${ACTIVE_BG}` : '1px solid transparent',
          userSelect:   'none',
          whiteSpace:   'nowrap',
          boxSizing:    'border-box',
          marginBottom: isActive ? '-1px' : '0',
          transition:   'background 0.1s, color 0.1s',
        }}
        onMouseEnter={e => {
          if (!isActive)
            (e.currentTarget as HTMLElement).style.background = INACTIVE_HOV
        }}
        onMouseLeave={e => {
          if (!isActive)
            (e.currentTarget as HTMLElement).style.background = INACTIVE_BG
        }}
      >
        <TabIcon status={tab.status} isActive={isActive} />

        <span style={{ maxWidth: '120px', overflow: 'hidden', textOverflow: 'ellipsis' }}>
          {tab.title}
        </span>

        <button
          onClick={e => { e.stopPropagation(); onClose() }}
          style={{
            background:     'none',
            border:         'none',
            cursor:         'pointer',
            padding:        '2px',
            display:        'flex',
            alignItems:     'center',
            justifyContent: 'center',
            color:          'transparent',
            borderRadius:   '3px',
            flexShrink:     0,
            marginLeft:     '2px',
            width:          '18px',
            height:         '18px',
          }}
          onMouseEnter={e => {
            e.stopPropagation()
            e.currentTarget.style.color      = '#1a1a1a'
            e.currentTarget.style.background = 'rgba(0,0,0,0.08)'
          }}
          onMouseLeave={e => {
            e.stopPropagation()
            e.currentTarget.style.color      = 'transparent'
            e.currentTarget.style.background = 'none'
          }}
        >
          <X size={11} />
        </button>
      </div>
    </div>
  )
}

export default function TabBar({
  tabs,
  activeTabId,
  onSelect,
  onAdd,
  onClose,
  onReorder,
}: TabBarProps) {
  const sensors = useSensors(
    useSensor(PointerSensor, { activationConstraint: { distance: 5 } }),
  )

  const handleDragEnd = (event: DragEndEvent) => {
    const { active, over } = event
    if (!over || active.id === over.id) return
    const oldIndex = tabs.findIndex(t => t.id === active.id)
    const newIndex = tabs.findIndex(t => t.id === over.id)
    onReorder(arrayMove(tabs, oldIndex, newIndex))
  }

  return (
    <>
      <style>{`
        @keyframes tabSpin {
          from { transform: rotate(0deg); }
          to   { transform: rotate(360deg); }
        }
      `}</style>

      <div style={{
        display:        'flex',
        alignItems:     'stretch',
        height:         '36px',
        background:     TAB_BAR_BG,
        overflowX:      'auto',
        overflowY:      'visible',
        flexShrink:     0,
        scrollbarWidth: 'none',
      }}>
        <DndContext
          sensors={sensors}
          collisionDetection={closestCenter}
          onDragEnd={handleDragEnd}
        >
          <SortableContext
            items={tabs.map(t => t.id)}
            strategy={horizontalListSortingStrategy}
          >
            {tabs.map(tab => (
              <SortableTab
                key={tab.id}
                tab={tab}
                isActive={tab.id === activeTabId}
                onSelect={() => onSelect(tab.id)}
                onClose={() => onClose(tab.id)}
              />
            ))}
          </SortableContext>
        </DndContext>

        <button
          onClick={onAdd}
          title="New query"
          style={{
            background: 'none',
            border:     'none',
            cursor:     'pointer',
            padding:    '0 10px',
            display:    'flex',
            alignItems: 'center',
            color:      '#9aa0a6',
            flexShrink: 0,
            transition: 'color 0.15s, background 0.15s',
          }}
          onMouseEnter={e => {
            e.currentTarget.style.background = INACTIVE_HOV
            e.currentTarget.style.color      = '#1a1a1a'
          }}
          onMouseLeave={e => {
            e.currentTarget.style.background = 'none'
            e.currentTarget.style.color      = '#9aa0a6'
          }}
        >
          <Plus size={14} />
        </button>
      </div>
    </>
  )
}