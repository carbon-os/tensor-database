import { Clock } from 'lucide-react'
import type { QueryResult, QueryTab } from '../types'

interface Props {
  result: QueryResult | null
  status: QueryTab['status']
}

export default function ResultsPanel({ result, status }: Props) {
  if (status === 'idle') {
    return (
      <Empty>Run a query to see results</Empty>
    )
  }

  if (status === 'running') {
    return (
      <Empty>Executing...</Empty>
    )
  }

  if (!result) return null

  return (
    <div style={{ flex: 1, display: 'flex', flexDirection: 'column', overflow: 'hidden', minHeight: 0 }}>
      {/* status bar */}
      <div style={{
        display: 'flex',
        alignItems: 'center',
        gap: '16px',
        padding: '5px 12px',
        borderBottom: '0.5px solid var(--color-border-tertiary)',
        background: 'var(--color-background-secondary)',
        fontSize: '12px',
        color: 'var(--color-text-secondary)',
        flexShrink: 0,
      }}>
        <span>{result.rowCount.toLocaleString()} rows</span>
        <span style={{ display: 'flex', alignItems: 'center', gap: '4px' }}>
          <Clock size={12} />
          {result.durationMs}ms
        </span>
      </div>

      {/* table */}
      <div style={{ flex: 1, overflowY: 'auto', overflowX: 'auto' }}>
        <table style={{
          width: '100%',
          borderCollapse: 'collapse',
          fontSize: '13px',
        }}>
          <thead>
            <tr>
              {result.columns.map(col => (
                <th key={col} style={{
                  position: 'sticky',
                  top: 0,
                  padding: '7px 12px',
                  textAlign: 'left',
                  fontWeight: 500,
                  fontSize: '12px',
                  color: 'var(--color-text-secondary)',
                  background: 'var(--color-background-secondary)',
                  borderBottom: '0.5px solid var(--color-border-tertiary)',
                  whiteSpace: 'nowrap',
                }}>
                  {col}
                </th>
              ))}
            </tr>
          </thead>
          <tbody>
            {result.rows.map((row, i) => (
              <tr
                key={i}
                style={{ borderBottom: '0.5px solid var(--color-border-tertiary)' }}
              >
                {result.columns.map(col => (
                  <td key={col} style={{
                    padding: '7px 12px',
                    color: 'var(--color-text-primary)',
                    whiteSpace: 'nowrap',
                    maxWidth: '320px',
                    overflow: 'hidden',
                    textOverflow: 'ellipsis',
                  }}>
                    {String(row[col] ?? '')}
                  </td>
                ))}
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </div>
  )
}

function Empty({ children }: { children: React.ReactNode }) {
  return (
    <div style={{
      flex: 1,
      display: 'flex',
      alignItems: 'center',
      justifyContent: 'center',
      color: 'var(--color-text-tertiary)',
      fontSize: '13px',
    }}>
      {children}
    </div>
  )
}