import { useState } from 'react'
import { ChevronRight, ChevronDown, Database } from 'lucide-react'
import type { DbSchema, DbTable } from '../types'

interface Props {
  databases:    DbSchema[]
  onTableClick: (tableName: string) => void
}

export default function Sidebar({ databases, onTableClick }: Props) {
  const [expandedDbs, setExpandedDbs]       = useState<Set<string>>(new Set(['chinook']))
  const [expandedTables, setExpandedTables] = useState<Set<string>>(new Set())

  const toggleDb = (id: string) =>
    setExpandedDbs(prev => {
      const next = new Set(prev)
      next.has(id) ? next.delete(id) : next.add(id)
      return next
    })

  const toggleTable = (key: string) =>
    setExpandedTables(prev => {
      const next = new Set(prev)
      next.has(key) ? next.delete(key) : next.add(key)
      return next
    })

  return (
    <>
      <style>{`
        .sidebar-scroll {
          scrollbar-width: thin;
          scrollbar-color: transparent transparent;
          transition: scrollbar-color 0.3s;
        }
        .sidebar-scroll:hover {
          scrollbar-color: rgba(0,0,0,0.18) transparent;
        }
        .sidebar-scroll::-webkit-scrollbar {
          width: 4px;
        }
        .sidebar-scroll::-webkit-scrollbar-track {
          background: transparent;
        }
        .sidebar-scroll::-webkit-scrollbar-thumb {
          background: transparent;
          border-radius: 4px;
          transition: background 0.3s;
        }
        .sidebar-scroll:hover::-webkit-scrollbar-thumb {
          background: rgba(0,0,0,0.18);
        }
      `}</style>

      <div
        className="sidebar-scroll"
        style={{
          height:     '100%',
          overflowY:  'auto',
          background: 'var(--color-background-secondary)',
          padding:    '8px 0',
        }}
      >
        <div style={{
          padding:       '6px 12px 10px',
          fontSize:      '11px',
          fontWeight:    500,
          color:         'var(--color-text-tertiary)',
          letterSpacing: '0.06em',
          textTransform: 'uppercase',
        }}>
          Explorer
        </div>

        {databases.map(db => (
          <div key={db.id}>
            <button className="db-row" onClick={() => toggleDb(db.id)}>
              {expandedDbs.has(db.id)
                ? <ChevronDown  size={13} style={{ color: 'var(--color-text-tertiary)', flexShrink: 0 }} />
                : <ChevronRight size={13} style={{ color: 'var(--color-text-tertiary)', flexShrink: 0 }} />
              }
              <Database size={13} style={{ color: 'var(--color-text-secondary)', flexShrink: 0 }} />
              <span>{db.name}</span>
            </button>

            {expandedDbs.has(db.id) && db.tables.map(table => {
              const key = `${db.id}.${table.name}`
              return (
                <TableNode
                  key={key}
                  table={table}
                  expanded={expandedTables.has(key)}
                  onToggle={() => toggleTable(key)}
                  onClick={() => onTableClick(table.name)}
                />
              )
            })}
          </div>
        ))}
      </div>
    </>
  )
}

function TableNode({ table, expanded, onToggle, onClick }: {
  table:    DbTable
  expanded: boolean
  onToggle: () => void
  onClick:  () => void
}) {
  return (
    <div>
      <div className="table-row">
        <button
          onClick={onToggle}
          style={{
            background: 'none',
            border:     'none',
            cursor:     'pointer',
            padding:    0,
            display:    'flex',
            alignItems: 'center',
            color:      'var(--color-text-tertiary)',
            flexShrink: 0,
          }}
        >
          {expanded
            ? <ChevronDown  size={12} />
            : <ChevronRight size={12} />
          }
        </button>
        <span onClick={onClick} style={{ flex: 1 }}>{table.name}</span>
      </div>

      {expanded && table.columns.map(col => (
        <div
          key={col.name}
          style={{
            display:        'flex',
            justifyContent: 'space-between',
            padding:        '2px 12px 2px 52px',
            fontSize:       '12px',
            color:          'var(--color-text-tertiary)',
          }}
        >
          <span>{col.name}</span>
          <span style={{ opacity: 0.6, fontSize: '11px' }}>{col.type}</span>
        </div>
      ))}
    </div>
  )
}