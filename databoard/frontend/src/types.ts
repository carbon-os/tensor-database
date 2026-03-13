export type Theme = 'light' | 'dark'

export interface DbColumn {
  name: string
  type: string
}

export interface DbTable {
  name: string
  columns: DbColumn[]
}

export interface DbSchema {
  id: string
  name: string
  tables: DbTable[]
}

export interface QueryResult {
  columns: string[]
  rows: Record<string, unknown>[]
  rowCount: number
  durationMs: number
}

export interface QueryTab {
  id: string
  title: string
  query: string
  result: QueryResult | null
  status: 'idle' | 'running' | 'done' | 'error'
}