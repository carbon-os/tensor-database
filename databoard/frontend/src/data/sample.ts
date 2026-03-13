import type { DbSchema, QueryResult } from '../types'

export const SAMPLE_DBS: DbSchema[] = [
  {
    id: 'chinook',
    name: 'chinook',
    tables: [
      {
        name: 'album',
        columns: [
          { name: 'AlbumId',  type: 'int32' },
          { name: 'Title',    type: 'text' },
          { name: 'ArtistId', type: 'int32' },
        ],
      },
      {
        name: 'artist',
        columns: [
          { name: 'ArtistId', type: 'int32' },
          { name: 'Name',     type: 'text' },
        ],
      },
      {
        name: 'track',
        columns: [
          { name: 'TrackId',      type: 'int32' },
          { name: 'Name',         type: 'text' },
          { name: 'AlbumId',      type: 'int32' },
          { name: 'Milliseconds', type: 'int32' },
          { name: 'UnitPrice',    type: 'decimal(10,2)' },
        ],
      },
      {
        name: 'customer',
        columns: [
          { name: 'CustomerId', type: 'int32' },
          { name: 'FirstName',  type: 'text' },
          { name: 'LastName',   type: 'text' },
          { name: 'Email',      type: 'text' },
          { name: 'Country',    type: 'text' },
        ],
      },
      {
        name: 'invoice',
        columns: [
          { name: 'InvoiceId',   type: 'int32' },
          { name: 'CustomerId',  type: 'int32' },
          { name: 'InvoiceDate', type: 'timestamp' },
          { name: 'Total',       type: 'decimal(10,2)' },
        ],
      },
      {
        name: 'genre',
        columns: [
          { name: 'GenreId', type: 'int32' },
          { name: 'Name',    type: 'text' },
        ],
      },
    ],
  },
  {
    id: 'analytics',
    name: 'analytics',
    tables: [
      {
        name: 'events',
        columns: [
          { name: 'event_id',   type: 'uuid' },
          { name: 'user_id',    type: 'int32' },
          { name: 'event_name', type: 'text' },
          { name: 'timestamp',  type: 'timestamp' },
        ],
      },
      {
        name: 'sessions',
        columns: [
          { name: 'session_id', type: 'uuid' },
          { name: 'user_id',    type: 'int32' },
          { name: 'started_at', type: 'timestamp' },
          { name: 'duration_s', type: 'int32' },
        ],
      },
    ],
  },
  {
    id: 'rivers',
    name: 'rivers',
    tables: [
      {
        name: 'measurements',
        columns: [
          { name: 'id',          type: 'int32' },
          { name: 'river_name',  type: 'text' },
          { name: 'flow_rate',   type: 'float64' },
          { name: 'recorded_at', type: 'timestamp' },
        ],
      },
    ],
  },
]

export const SAMPLE_RESULTS: Record<string, QueryResult> = {
  album: {
    columns: ['AlbumId', 'Title', 'ArtistId'],
    rows: [
      { AlbumId: 1, Title: 'For Those About to Rock We Salute You', ArtistId: 1 },
      { AlbumId: 2, Title: 'Balls to the Wall',                     ArtistId: 2 },
      { AlbumId: 3, Title: 'Restless and Wild',                     ArtistId: 2 },
      { AlbumId: 4, Title: 'Let There Be Rock',                     ArtistId: 1 },
      { AlbumId: 5, Title: 'Big Ones',                              ArtistId: 3 },
      { AlbumId: 6, Title: 'Jagged Little Pill',                    ArtistId: 4 },
      { AlbumId: 7, Title: 'Facelift',                              ArtistId: 5 },
      { AlbumId: 8, Title: 'Warner 25 Anos',                        ArtistId: 6 },
      { AlbumId: 9, Title: 'Plays Metallica by Four Cellos',        ArtistId: 7 },
      { AlbumId: 10, Title: 'Audioslave',                           ArtistId: 8 },
    ],
    rowCount: 347,
    durationMs: 12,
  },
  artist: {
    columns: ['ArtistId', 'Name'],
    rows: [
      { ArtistId: 1, Name: 'AC/DC' },
      { ArtistId: 2, Name: 'Accept' },
      { ArtistId: 3, Name: 'Aerosmith' },
      { ArtistId: 4, Name: 'Alanis Morissette' },
      { ArtistId: 5, Name: 'Alice In Chains' },
      { ArtistId: 6, Name: 'Antônio Carlos Jobim' },
      { ArtistId: 7, Name: 'Apocalyptica' },
      { ArtistId: 8, Name: 'Audioslave' },
    ],
    rowCount: 275,
    durationMs: 8,
  },
  track: {
    columns: ['TrackId', 'Name', 'AlbumId', 'Milliseconds', 'UnitPrice'],
    rows: [
      { TrackId: 1, Name: 'For Those About to Rock',  AlbumId: 1, Milliseconds: 343719, UnitPrice: '0.99' },
      { TrackId: 2, Name: 'Balls to the Wall',        AlbumId: 2, Milliseconds: 342562, UnitPrice: '0.99' },
      { TrackId: 3, Name: 'Fast as a Shark',          AlbumId: 3, Milliseconds: 230619, UnitPrice: '0.99' },
      { TrackId: 4, Name: 'Restless and Wild',        AlbumId: 3, Milliseconds: 252051, UnitPrice: '0.99' },
      { TrackId: 5, Name: 'Princess of the Dawn',     AlbumId: 3, Milliseconds: 375418, UnitPrice: '0.99' },
    ],
    rowCount: 3503,
    durationMs: 21,
  },
  customer: {
    columns: ['CustomerId', 'FirstName', 'LastName', 'Email', 'Country'],
    rows: [
      { CustomerId: 1, FirstName: 'Luís',     LastName: 'Gonçalves', Email: 'luisg@embraer.com.br', Country: 'Brazil' },
      { CustomerId: 2, FirstName: 'Leonie',   LastName: 'Köhler',    Email: 'leoniek@gmail.com',    Country: 'Germany' },
      { CustomerId: 3, FirstName: 'François', LastName: 'Tremblay',  Email: 'ftremblay@gmail.com',  Country: 'Canada' },
      { CustomerId: 4, FirstName: 'Bjørn',    LastName: 'Hansen',    Email: 'bjorn.hansen@yahoo.no', Country: 'Norway' },
      { CustomerId: 5, FirstName: 'František',LastName: 'Wichterlová',Email: 'frantisekw@jetbrains.com', Country: 'Czech Republic' },
    ],
    rowCount: 59,
    durationMs: 9,
  },
  invoice: {
    columns: ['InvoiceId', 'CustomerId', 'InvoiceDate', 'Total'],
    rows: [
      { InvoiceId: 1, CustomerId: 2, InvoiceDate: '2021-01-01T00:00:00Z', Total: '1.98' },
      { InvoiceId: 2, CustomerId: 4, InvoiceDate: '2021-01-02T00:00:00Z', Total: '3.96' },
      { InvoiceId: 3, CustomerId: 8, InvoiceDate: '2021-01-03T00:00:00Z', Total: '5.94' },
      { InvoiceId: 4, CustomerId: 14,InvoiceDate: '2021-01-06T00:00:00Z', Total: '8.91' },
      { InvoiceId: 5, CustomerId: 23,InvoiceDate: '2021-01-11T00:00:00Z', Total: '13.86' },
    ],
    rowCount: 412,
    durationMs: 14,
  },
  genre: {
    columns: ['GenreId', 'Name'],
    rows: [
      { GenreId: 1,  Name: 'Rock' },
      { GenreId: 2,  Name: 'Jazz' },
      { GenreId: 3,  Name: 'Metal' },
      { GenreId: 4,  Name: 'Alternative & Punk' },
      { GenreId: 5,  Name: 'Rock And Roll' },
      { GenreId: 6,  Name: 'Blues' },
      { GenreId: 7,  Name: 'Latin' },
      { GenreId: 8,  Name: 'Reggae' },
    ],
    rowCount: 25,
    durationMs: 5,
  },
  events: {
    columns: ['event_id', 'user_id', 'event_name', 'timestamp'],
    rows: [
      { event_id: 'a1b2c3d4-0001', user_id: 101, event_name: 'page_view',     timestamp: '2025-03-01T08:12:00Z' },
      { event_id: 'a1b2c3d4-0002', user_id: 102, event_name: 'button_click',  timestamp: '2025-03-01T08:13:22Z' },
      { event_id: 'a1b2c3d4-0003', user_id: 101, event_name: 'form_submit',   timestamp: '2025-03-01T08:15:04Z' },
      { event_id: 'a1b2c3d4-0004', user_id: 103, event_name: 'page_view',     timestamp: '2025-03-01T08:17:45Z' },
      { event_id: 'a1b2c3d4-0005', user_id: 104, event_name: 'session_start', timestamp: '2025-03-01T08:20:11Z' },
    ],
    rowCount: 84201,
    durationMs: 38,
  },
  sessions: {
    columns: ['session_id', 'user_id', 'started_at', 'duration_s'],
    rows: [
      { session_id: 'sess-0001', user_id: 101, started_at: '2025-03-01T08:10:00Z', duration_s: 312 },
      { session_id: 'sess-0002', user_id: 102, started_at: '2025-03-01T08:13:00Z', duration_s: 87  },
      { session_id: 'sess-0003', user_id: 103, started_at: '2025-03-01T08:17:00Z', duration_s: 540 },
      { session_id: 'sess-0004', user_id: 104, started_at: '2025-03-01T08:20:00Z', duration_s: 204 },
    ],
    rowCount: 19847,
    durationMs: 22,
  },
  measurements: {
    columns: ['id', 'river_name', 'flow_rate', 'recorded_at'],
    rows: [
      { id: 1, river_name: 'Thames',    flow_rate: 65.4,  recorded_at: '2025-02-01T06:00:00Z' },
      { id: 2, river_name: 'Thames',    flow_rate: 70.1,  recorded_at: '2025-02-02T06:00:00Z' },
      { id: 3, river_name: 'Severn',    flow_rate: 120.8, recorded_at: '2025-02-01T06:00:00Z' },
      { id: 4, river_name: 'Severn',    flow_rate: 115.3, recorded_at: '2025-02-02T06:00:00Z' },
      { id: 5, river_name: 'Trent',     flow_rate: 88.2,  recorded_at: '2025-02-01T06:00:00Z' },
    ],
    rowCount: 1430,
    durationMs: 11,
  },
  default: {
    columns: ['id', 'name', 'value', 'created_at'],
    rows: [
      { id: 1, name: 'alpha',   value: 42.5, created_at: '2025-01-01T00:00:00Z' },
      { id: 2, name: 'beta',    value: 18.2, created_at: '2025-01-02T00:00:00Z' },
      { id: 3, name: 'gamma',   value: 99.0, created_at: '2025-01-03T00:00:00Z' },
      { id: 4, name: 'delta',   value: 3.7,  created_at: '2025-01-04T00:00:00Z' },
      { id: 5, name: 'epsilon', value: 55.1, created_at: '2025-01-05T00:00:00Z' },
    ],
    rowCount: 5,
    durationMs: 6,
  },
}