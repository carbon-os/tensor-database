import type * as Monaco from 'monaco-editor'

export const TQL_LANGUAGE_ID = 'tql'

// ── Token lists pulled directly from TQLLexer.g4 ─────────────────────────────

const PIPELINE_KEYWORDS = [
  'from', 'join', 'left', 'where', 'group', 'by', 'let', 'having',
  'select', 'order', 'asc', 'desc', 'limit', 'as', 'on',
]

const MUTATION_KEYWORDS = [
  'insert', 'into', 'update', 'set', 'delete', 'returning',
  'upsert', 'conflict', 'values',
]

const DDL_KEYWORDS = [
  'create', 'table', 'role', 'grant', 'to', 'allow', 'deny',
  'read', 'write', 'revoke', 'api_key', 'for', 'expires', 'in', 'truncate',
]

const PACKAGE_KEYWORDS = ['import', 'package', 'type']

const TYPE_KEYWORDS = [
  'int32', 'int64', 'float32', 'float64', 'decimal',
  'bool', 'text', 'uuid', 'timestamp', 'json', 'array', 'vector', 'map',
]

const BUILTIN_FUNCTIONS = [
  'gen_uuid', 'now', 'match', 'embed', 'prompt',
  'count', 'sum', 'avg', 'min', 'max',
]

const CONSTANTS = ['null', 'true', 'false']

const ALL_KEYWORDS = [
  ...PIPELINE_KEYWORDS,
  ...MUTATION_KEYWORDS,
  ...DDL_KEYWORDS,
  ...PACKAGE_KEYWORDS,
  'and', 'or', 'not',
]

// ── Module-level guard so registration only runs once ─────────────────────────
let registered = false

export function registerTqlLanguage(monaco: typeof Monaco): void {
  if (registered) return
  registered = true

  monaco.languages.register({ id: TQL_LANGUAGE_ID, extensions: ['.tql'] })

  // ── Monarch tokenizer ───────────────────────────────────────────────────────
  monaco.languages.setMonarchTokensProvider(TQL_LANGUAGE_ID, {
    keywords: ALL_KEYWORDS,
    typeKeywords: TYPE_KEYWORDS,
    builtins: BUILTIN_FUNCTIONS,
    constants: CONSTANTS,

    tokenizer: {
      root: [
        // Line comments (only valid comment style per grammar)
        [/\/\/.*$/, 'comment'],

        // Double-quoted strings (paths, text values, api key ids)
        [/"([^"\\]|\\.)*"/, 'string'],

        // Single-quoted strings (json<> inline values only)
        [/'([^'\\]|\\.)*'/, 'string.json'],

        // Duration literals — must precede INTEGER so '90d' doesn't split
        [/[0-9]+d\b/, 'number.duration'],

        // Float literals — must precede INTEGER
        [/[0-9]+\.[0-9]+/, 'number.float'],

        // Integer literals
        [/[0-9]+/, 'number'],

        // Vec distance operator <-> (only valid in order by — parser enforces)
        [/<->/, 'operator.vec'],

        // Multi-char operators — must precede single-char prefixes
        [/==|!=|<=|>=/, 'operator'],

        // Single-char operators
        [/[<>+\-*/]/, 'operator'],

        // Assignment (let clause only)
        [/=/, 'operator.assign'],

        // Punctuation
        [/[{}()[\],.:?]/, 'delimiter'],

        // _mutation compiler-provided field — before IDENTIFIER rule
        [/_mutation\b/, 'constant.special'],

        // Identifiers and reserved words
        [/[a-zA-Z_][a-zA-Z0-9_]*/, {
          cases: {
            '@keywords':     'keyword',
            '@typeKeywords': 'type',
            '@builtins':     'function',
            '@constants':    'constant',
            '@default':      'identifier',
          },
        }],

        // Whitespace
        [/[ \t\r\n]+/, 'white'],
      ],
    },
  })

  // ── Themes ────────────────────────────────────────────────────────────────
  monaco.editor.defineTheme('tql-dark', {
    base: 'vs-dark',
    inherit: true,
    rules: [
      { token: 'keyword',          foreground: '569CD6', fontStyle: 'bold' },
      { token: 'type',             foreground: '4EC9B0' },
      { token: 'function',         foreground: 'DCDCAA' },
      { token: 'constant',         foreground: '569CD6' },
      { token: 'constant.special', foreground: 'C586C0', fontStyle: 'bold' },
      { token: 'string',           foreground: 'CE9178' },
      { token: 'string.json',      foreground: 'CE9178', fontStyle: 'italic' },
      { token: 'number',           foreground: 'B5CEA8' },
      { token: 'number.float',     foreground: 'B5CEA8' },
      { token: 'number.duration',  foreground: 'B5CEA8', fontStyle: 'italic' },
      { token: 'operator',         foreground: 'D4D4D4' },
      { token: 'operator.vec',     foreground: 'C586C0', fontStyle: 'bold' },
      { token: 'operator.assign',  foreground: 'D4D4D4' },
      { token: 'comment',          foreground: '6A9955', fontStyle: 'italic' },
      { token: 'delimiter',        foreground: 'D4D4D4' },
      { token: 'identifier',       foreground: 'D4D4D4' },
    ],
    colors: {
      'editor.background':          '#1e1e1e',
      'editor.lineHighlightBorder': '#00000000',
      'editorLineNumber.foreground': '#4a4a4a',
    },
  })

  monaco.editor.defineTheme('tql-light', {
    base: 'vs',
    inherit: true,
    rules: [
      { token: 'keyword',          foreground: '0000FF', fontStyle: 'bold' },
      { token: 'type',             foreground: '267F99' },
      { token: 'function',         foreground: '795E26' },
      { token: 'constant',         foreground: '0070C1' },
      { token: 'constant.special', foreground: 'AF00DB', fontStyle: 'bold' },
      { token: 'string',           foreground: 'A31515' },
      { token: 'string.json',      foreground: 'A31515', fontStyle: 'italic' },
      { token: 'number',           foreground: '098658' },
      { token: 'number.float',     foreground: '098658' },
      { token: 'number.duration',  foreground: '098658', fontStyle: 'italic' },
      { token: 'operator',         foreground: '000000' },
      { token: 'operator.vec',     foreground: 'AF00DB', fontStyle: 'bold' },
      { token: 'operator.assign',  foreground: '000000' },
      { token: 'comment',          foreground: '008000', fontStyle: 'italic' },
      { token: 'delimiter',        foreground: '000000' },
    ],
    colors: {
      'editor.lineHighlightBorder': '#00000000',
    },
  })

  // ── Autocomplete ──────────────────────────────────────────────────────────
  monaco.languages.registerCompletionItemProvider(TQL_LANGUAGE_ID, {
    provideCompletionItems(model, position) {
      const word  = model.getWordUntilPosition(position)
      const range = {
        startLineNumber: position.lineNumber,
        endLineNumber:   position.lineNumber,
        startColumn:     word.startColumn,
        endColumn:       word.endColumn,
      }

      const kw = (label: string) => ({
        label,
        kind: monaco.languages.CompletionItemKind.Keyword,
        insertText: label,
        range,
      })

      const ty = (label: string) => ({
        label,
        kind: monaco.languages.CompletionItemKind.Class,
        insertText: label,
        range,
      })

      const fn = (label: string, snippet: string) => ({
        label,
        kind: monaco.languages.CompletionItemKind.Function,
        insertText: snippet,
        insertTextRules: monaco.languages.CompletionItemInsertTextRule.InsertAsSnippet,
        range,
      })

      return {
        suggestions: [
          ...ALL_KEYWORDS.map(kw),
          ...TYPE_KEYWORDS.map(ty),

          // Built-ins with snippet stubs matching grammar arities
          fn('gen_uuid',  'gen_uuid()'),
          fn('now',       'now()'),
          fn('match',     'match(${1:field}, ${2:"token"})'),
          fn('embed',     'embed(${1:"query"})'),
          fn('prompt',    'prompt(${1:field}, ${2:"instruction"}, ${3:OutputType})'),
          fn('count',     'count(${1:*})'),
          fn('sum',       'sum(${1:field})'),
          fn('avg',       'avg(${1:field})'),
          fn('min',       'min(${1:field})'),
          fn('max',       'max(${1:field})'),

          ...CONSTANTS.map(kw),

          { label: '_mutation', kind: monaco.languages.CompletionItemKind.Field,
            insertText: '_mutation', detail: 'compiler-provided mutation info', range },
        ],
      }
    },
  })
}