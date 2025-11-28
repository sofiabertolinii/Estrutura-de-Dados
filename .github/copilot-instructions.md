This repository contains multiple small C exercises for data structures (trees, lists, graphs).

Goal for an automated coding agent
- Be conservative: modify only files inside the specific exercise folder you are asked to work on (e.g. `Grafos/grafos4/*`).
- Prefer small, focused edits that implement the requested algorithm and keep the existing interfaces in `grafo.h` unchanged.

Important project patterns and conventions
- Each exercise is a self-contained folder under the top-level directories (for example `Grafos/grafos4/`). Edit only inside that folder unless a global change is explicitly requested.
- Public interfaces are declared in `*.h` files (for example `Grafos/grafos4/grafo.h`). Keep function prototypes and signatures stable.
- Memory is manually allocated/freed (malloc/free). Follow existing allocation style and free any additional memory you allocate.
- Simple linked-list queue is implemented in `Grafos/grafos4/main.c` using the `Item` and `Lista` types. New code should reuse these types and helper functions (`cria_lista`, `adiciona_item`, `busca_item`) when implementing BFS/shortest-path.

Specific guidance for `Grafos/grafos4` (shortest path task)
- The assignment in `Grafos/grafos4/main.c` expects an implementation of:
  - void menor_caminho (Grafo * grafo, Vertice * origem, Vertice * destino);

- Implement BFS (breadth-first search) using the provided `Lista` queue helpers. Requirements:
  - Stop expanding when you dequeue an item whose `vertice` equals `destino` — the first time you reach `destino` yields the shortest path in an unweighted graph.
  - Extend the `Item` struct's `precedente` field to point to the Item that caused the enqueued vertex (this field already exists in `main.c`; set it when enqueueing).
  - After finding `destino`, reconstruct the path by following `precedente` pointers from the destination `Item` back to the initial `Item`, then print vertices in origin→...→destination order.
  - If `destino` is unreachable, print a clear message (for example: "Vertices nao estao conectados").
  - Use `grafo_busca_vertices_saida` to enumerate outgoing neighbors of a vertex.
  - Use `busca_item` to avoid visiting the same vertex twice (mark visited by presence in the queue/list).

Examples from the codebase
- `Grafos/grafos4/grafo.h` defines the API used by `main.c` (look for `grafo_cria`, `grafo_insere_aresta`, `grafo_busca_vertices_saida`).
- `Grafos/grafos4/grafo.c` stores adjacency as a matrix with -1 representing no edge; any value >=0 is an edge cost. For BFS treat existence ( != -1 ) as an unweighted edge.
- `Grafos/grafos4/main.c` contains helper functions:
  - `Lista * cria_lista()` — create queue
  - `Item * adiciona_item(Lista * lista, Vertice * vertice)` — append to queue; set `precedente` to NULL by default
  - `Item * busca_item(Lista * lista, Vertice * vertice)` — linear search to check visited vertices

Testing and running
- There is no build system file; compile the exercise folder manually. From the `Grafos/grafos4` folder run (PowerShell):
  gcc -o main main.c grafo.c
  .\main

What to avoid
- Don't change API declarations in `grafo.h` or move helper functions into global scope.
- Avoid adding external dependencies — keep to standard C library only.

If anything is unclear
- Ask which folder/exercise to modify and whether you may change header prototypes. If the user asks to implement multiple exercises, propose separate commits/PRs per folder.

End of instructions
