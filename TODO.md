# TODO

## Milestone Dpendency Chain

```
M01: Seek & Flee
  └─► M02: Obstacle Avoidance
       └─► M03: Gradient Descent
            ├─► M04: Moving Obstacles
            │    └─► M08: Dynamic Flow Re-compute
            ├─► M05: Pheromone Trails
            │    └─► M06: Lane Formation
            │         └─► M10: Hybrid System
            ├─► M07: Flow Field Swarms
            │    └─► M08: Dynamic Flow Re-compute
            └─► M09: Q-Learning Ants
                 └─► M10: Hybrid System
```

## Milestones

### Seek & Flee

- One agent chases or runs from the mouse; hold a key to swap mode
- Agent only knows its position + target offset

### Obstacle Avoidance

- Agent glides around shapes
- Local = within sensor radius

### Gradient Descent on a Static Map

- Agent slides straight to goal; gradient shown as grey-scale heat-map
- Optimal path = follow −∇f

### Moving Obstacles

- Agent zig-zags through constantly changing gradient
- Field recomputed only around obstacles (cheap)

### Pheromone Trails (bridge milestone)

- Introduce memory/learning/sensing, state-action-reward
- Bright trails fade over time; ants find food source and return, forming shortest path without a map
- Agents read **3 forward sensors**, pick strongest

### Emergent Lane Formation

- Two-lane highway appears; block one tunnel with a wall—ants automatically reroute

### Flow-Field Swarms

- Instant perfect routing; overlay arrow layer (UI on/off)
- No per-agent A*; O(1) lookup

### Dynamic Flow Re-compute

- Swarm changes corridor **within 0.2 s** on old laptop
- Combine **global pre-compute** with **local updates**

### Tabular Q-Learning Ants

- Heat-map of max Q; ants **learn pheromone-free shortcut** after 500 episodes
- Only **local state** (8 adjacent tiles) stored

### Hybrid System

- Watch **initial random → perfect lane → pheromone reinforced**
- Separates **exploration memory** from **exploitation signal**

