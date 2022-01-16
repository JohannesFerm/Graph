//Johannes Ferm

typedef struct nod
{
	int vertexnmbr;
	struct nod *edgefrwd; //in case of directed graph
	struct nod *edgeback; //in case of undirected graph
	int weight;
	int dist;
}nod;

typedef struct list
{
	nod *first;
}list;

typedef struct graph //graph data-structure
{
	int size;
	list *firstnodes;	 //an array of lists
}graph;

typedef struct Snod //nodes for the stack
{
	int value;
	struct Snod *next;
}Snod;

typedef struct stack
{
	Snod *top;
}stack;

nod *create_nod(int x);

list *create_list();

graph *create_graph(int n);

int getNumVertices(graph *G);

int getNumEdges(graph *G);

list getNeighbors(graph *g, nod *x);

void addDirEdge(graph *g, int index, int vertexnr);

void addEdge(graph * g, int index, int vertexnr);

void addEdgeW(graph * g, int index, int vertexnr, int w);

void addDirEdgeW(graph *g, int index, int vertexnr, int w);

void print_list(list *l);

void print_graph(graph *g);

int hasEdge(graph *g, int index, int vertexnr);

list getOutNeighbors(graph *g, nod *x);

list *getInNeighbors(graph *g, int index);

void print_listW(list *l);

void print_graphW(graph *g);

graph *transpose(graph *g);

void SCC(graph *g, graph *gT);

void DFS(graph *gr, int v, int *vst);

void StackFill(graph *g,int i, int *vst, int *stack);

void init_single_src(graph *g, int source);

int relax(graph *g, nod *start, nod *end);

_Bool bellman_ford(graph *g, nod *source);

list *getDirNeighbors(graph *g, int index);

stack *init(stack *S);

void push(stack *S, int n);

Snod *pop(stack *S);

void SCC2(graph *g, int nodes);

//void findTrueMinDist(graph *g);
