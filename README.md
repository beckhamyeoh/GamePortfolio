# Game Portfolio

**Live site → <https://beckhamyeoh.github.io/GamePortfolio/>**

A collection of small Unity games and prototypes, playable in the browser via
WebGL. Built with [Astro](https://astro.build) and deployed to GitHub Pages.

## Games

- **Space SHMUP** — vertical shoot-'em-up with stacking power-ups, varied enemy
  patterns, and a multi-phase boss
- **Prospector** — solitaire-style card game with Bézier-animated card movement
  and a scoring system
- **Apple Picker** — arcade catch-the-apples loop with scoring and lives
- **Mission Demolition** — Angry-Birds-style physics game; pull back and launch
  projectiles to topple structures
- **Boids** — flocking AI built from separation, alignment, and cohesion rules

## Tech

- Astro static site, with content collections for game metadata
- Unity WebGL builds served from `public/play/<slug>/`, kept separate from the
  `/games/<slug>/` info-page routes to avoid URL collisions
- Auto-deployed via GitHub Actions on every push to `main`

<details>
<summary>Local development & adding a game</summary>

### Local development

```bash
npm install
npm run dev      # http://localhost:4321/GamePortfolio
npm run build    # outputs to dist/
npm run preview  # serve the built site locally
```

### Adding a new game

1. Create `src/content/games/<slug>.md` with frontmatter:
   ```yaml
   ---
   title: "My Game"
   tagline: "Short description."
   year: 2026
   tech: ["Unity", "C#"]
   playable: false
   buildPath: "play/<slug>"
   order: 80
   ---
   ```
2. (Optional) Build the game's WebGL target from Unity into
   `public/play/<slug>/`. See `public/play/README.md` for details.
3. Flip `playable: true` once the WebGL build is in place.

</details>
