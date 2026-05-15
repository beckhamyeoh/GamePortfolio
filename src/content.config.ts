import { defineCollection, z } from 'astro:content';
import { glob } from 'astro/loaders';

const games = defineCollection({
  loader: glob({ pattern: '**/*.md', base: './src/content/games' }),
  schema: z.object({
    title: z.string(),
    tagline: z.string(),
    year: z.number().optional(),
    tech: z.array(z.string()).default([]),
    thumbnail: z.string().optional(),
    playable: z.boolean().default(false),
    buildPath: z.string().optional(),
    repo: z.string().url().optional(),
    order: z.number().default(100),
  }),
});

export const collections = { games };
