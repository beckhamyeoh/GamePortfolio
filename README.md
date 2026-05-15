# GamePortfolio

Static site for showcasing Unity games, deployed to GitHub Pages.

Live site: <https://beckhamyeoh.github.io/GamePortfolio/>

## Stack

- [Astro](https://astro.build) static site
- Game metadata in `src/content/games/*.md`
- WebGL builds served from `public/play/<slug>/` (kept separate from the
  `/games/<slug>/` info-page route to avoid URL collisions)
- Deployed via GitHub Actions on push to `main`

## Local development

```bash
npm install
npm run dev      # http://localhost:4321/GamePortfolio
npm run build    # outputs to dist/
npm run preview  # serve the built site locally
```

## Adding a new game

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

## Enabling GitHub Pages

After the first push to `main`:

1. Go to **Settings → Pages** on the GitHub repo.
2. Under **Build and deployment → Source**, choose **GitHub Actions**.
3. The first run of the `Deploy to GitHub Pages` workflow will publish the
   site at the URL above.
