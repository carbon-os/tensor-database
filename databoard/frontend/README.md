# Tensor Database — Frontend

React + TypeScript app built with Vite.

## Requirements

- Node.js 18+
- npm 9+

## Install Node.js

**macOS / Linux — via nvm (recommended)**
```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash

# Restart your terminal, then
nvm install 18
nvm use 18
```

**macOS — via Homebrew**
```bash
brew install node@18
```

**Windows — via winget**
```bash
winget install OpenJS.NodeJS.LTS
```

Or download directly from https://nodejs.org

---

## Setup

```bash
# Install dependencies
npm install
```

## Commands

```bash
# Start development server (http://localhost:3000)
npm run dev

# Type check
npx tsc --noEmit

# Production build
npm run build

# Preview production build locally
npm run preview
```

## Structure

```
src/
├── pages/                  # Route-level page components
│   └── HomePage.tsx
├── components/
│   ├── layout/             # App-wide layout (Navbar, Footer)
│   ├── home/               # Components specific to HomePage
│   └── ui/                 # Generic reusable atoms (Button, Card)
├── types/
│   └── index.ts            # Shared TypeScript interfaces
├── App.tsx                 # Router + theme setup
└── index.css               # CSS variables + global reset
```

## Environment Variables

Create a `.env.local` file in this directory to override defaults:

```bash
VITE_API_URL=http://localhost:8080
```

Variables must be prefixed with `VITE_` to be exposed to the client.