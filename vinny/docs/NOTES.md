# Ship of Harkinian / OoT Rendering Notes

## Display Lists

A display list is **not a complete object definition**. It is a stream of N64 graphics commands that tells the RSP/RDP how to render geometry.

Typical commands include:

- Load vertices (`gsSPVertex`)
- Load textures (`gsDPLoadTextureBlock`)
- Draw triangles (`gsSP1Triangle`, `gsSP2Triangles`)
- Change render state
- Call another display list (`gsSPDisplayList`)

Example:

```c
gsDPLoadTextureBlock(textureA, ...);
gsSPVertex(verticesA, 32, 0);
gsSP1Triangle(0, 1, 2, 0);
gsSPEndDisplayList();
```

### Data Stored Outside the Display List

Display lists reference external data:

| Component | Needed for Static Export? | Purpose |
|------------|------------|------------|
| Display Lists | Yes | Rendering commands |
| Vertex Data | Yes | Positions, UVs, colors |
| Texture Data | Yes | Material textures |
| Material State | Yes | Transparency, texture usage |
| Matrix Transforms | Usually No | World/skeleton transforms |
| Skeleton Data | No (static export) | Animated hierarchy |
| Animation Data | No (static export) | Joint motion |
| Actor State | No | Runtime game behavior |

---

## glTF Export Requirements

To export a static object (e.g. a Bomb) to glTF:

### Required

1. Root display list
2. All referenced child display lists
3. Vertex arrays referenced by `gsSPVertex`
4. Textures referenced by texture-loading commands
5. Basic material/render state information

### Not Required

- Actor code
- Collision
- Game behavior
- Skeletons (for non-animated export)
- Animation data

### Important: Display Lists Are Stateful

Display lists operate like a command stream:

```text
Load Texture A
Draw Triangles

Load Texture B
Draw More Triangles

Enable Transparency
Draw More Triangles
```

When converting to glTF:

1. Execute/simulate the display list.
2. Track current material state.
3. Split geometry when material state changes.

Result:

```text
Mesh
├─ Primitive 0 (Material A)
├─ Primitive 1 (Material B)
└─ Primitive 2 (Transparent Material)
```

### Typical Export Pipeline

```text
Root Display List
        ↓
Traverse Child Display Lists
        ↓
Resolve Vertices
        ↓
Resolve Textures
        ↓
Build Materials
        ↓
Generate glTF Mesh
```

---

# "Graph" in Ship of Harkinian

In SoH/OoT, **Graph** generally refers to the graphics framework and rendering context, not a mathematical graph.

Common examples:

```c
play->state.gfxCtx
Graph_OpenDisps(...)
Graph_CloseDisps(...)
```

---

## GraphicsContext

The central rendering object is:

```c
GraphicsContext* gfxCtx;
```

Conceptually:

```text
Frame
 └─ GraphicsContext
      ├─ Opaque Display List
      ├─ Translucent Display List
      ├─ Overlay Display List
      └─ Temporary Graphics Allocations
```

Actor draw functions append commands into these display-list buffers.

---

## What Graph Functions Do

Functions such as:

```c
Graph_OpenDisps(...)
Graph_CloseDisps(...)
```

primarily handle:

- Display-list buffer management
- Graphics memory allocation
- Debugging information
- Tracking display-list construction

They do **not** directly render geometry.

---

## Scene-Graph Usage

The engine also contains hierarchical rendering structures, especially for skeletons:

```text
Skeleton
├─ Root
│  ├─ Arm
│  └─ Head
└─ Leg
```

Rendering traverses the hierarchy:

```text
Skeleton
      ↓
Compute Limb Transform
      ↓
Execute Limb Display List
```

Functions such as:

```c
SkelAnime_Draw(...)
SkelAnime_DrawFlex(...)
```

perform this traversal.

---

## Relationship Between Graph and Display Lists

The Graph system manages the buffers used to build display lists.

Conceptually:

```text
Actor Draw Function
        ↓
GraphicsContext (Graph)
        ↓
Display List Buffers
        ↓
RSP Commands
        ↓
Rendered Geometry
```

For model extraction/export, the Graph system is usually not important.

The data of interest is:

```text
Display Lists
      ↓
Vertices
      ↓
Textures
      ↓
Materials
```

The Graph layer is primarily runtime infrastructure for assembling and managing rendering commands each frame.
