# Parser

ANTLR4-generated C++ lexer and parser for the Tensor Query Language (`.tql`).

---

## Structure
```
parser/
├── DBLexer.g4
├── DBParser.g4
├── README.md
└── src/           ← generated files land here, safe to delete and regenerate
```

---

## Prerequisites

**Java** — required to run the ANTLR tool jar.
```bash
sudo apt update && sudo apt install default-jdk -y
java -version
```

**ANTLR 4.13.2 jar**
```bash
wget http://www.antlr.org/download/antlr-4.13.2-complete.jar
```

Keep the jar in `parser/` next to the grammars, or adjust the path in the commands below.

---

## Generating
```bash
mkdir -p src

java -jar antlr-4.13.2-complete.jar \
  -Dlanguage=Cpp \
  -visitor \
  -no-listener \
  -o src/ \
  TQLLexer.g4 TQLParser.g4
```

The `src/` directory can be deleted and regenerated at any time — never edit files inside it by hand.

---

## Regenerating from Scratch
```bash
rm -rf src/

java -jar antlr-4.13.2-complete.jar \
  -Dlanguage=Cpp \
  -visitor \
  -no-listener \
  -o src/ \
  TQLLexer.g4 TQLParser.g4
```