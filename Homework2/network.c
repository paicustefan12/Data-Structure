#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pc {
	char *nume;
	char *ip;
	int stare;
}pc;

typedef struct router {
	char *nume;
	char *ip;
	int nr;
	int nr_pc;
	pc *p;
} router;

typedef struct Graph {
	int V;
	int E;
	int **a;
}Graph;

Graph create( FILE *f){
	int i, j;
    Graph g;
    fscanf(f, "%d", &g.V);
	g.a = (int**)malloc(g.V*sizeof(int*));
	for(i=0;i<g.V;i++)
		g.a[i] = (int*)malloc(g.V*sizeof(int));
	for(i=0;i<g.V;i++)
		for(j=0;j<g.V;j++)
			g.a[i][j] = 100000;
	return g;
}

void citire(Graph *g, router r[], FILE *f){
	char *nu1, *nu2;
	int nr1, nr2, val, i, j, k, l;


	nu1 = (char*)malloc(10*sizeof(char));
	nu2 = (char*)malloc(10*sizeof(char));

	for(i=0;i<g->V;i++){
		r[i].nume = (char*)malloc(10*sizeof(char));
		r[i].ip = (char*)malloc(12*sizeof(char));
		fscanf(f, "%s", r[i].nume);
		fscanf(f, "%s", r[i].ip);
		fscanf(f, "%d", &r[i].nr_pc);
		r[i].nr = i;
		if(r[i].nr_pc > 0)
			r[i].p = (pc*)malloc(r[i].nr_pc*sizeof(pc));
		for(j = 0; j < r[i].nr_pc;j++){
			r[i].p[j].nume = (char*)malloc(5*sizeof(char));
			r[i].p[j].ip = (char*)malloc(15*sizeof(char));
			fscanf(f, "%s", r[i].p[j].nume);
			fscanf(f, "%s", r[i].p[j].ip);
			fscanf(f, "%d", &r[i].p[j].stare);
		}
	}
	fscanf(f, "%d", &g->E);
	for(i=0;i<g->E;i++){
		fscanf(f, "%s", nu1);
		fscanf(f, "%s", nu2);
		if(strlen(nu1) == 7)
			nr1 = nu1[6] - '1';
		else if(strlen(nu1) == 8){
			k = nu1[6] - '0';
			l = nu1[7] - '1';
			nr1 = k*10+l;
		}
		if(strlen(nu2) == 7)
			nr2 = nu2[6] - '1';
		else if(strlen(nu2) == 8){
			k = nu2[6] - '0';
			l = nu2[7] - '1';
			nr2 = k*10+l;
		}
		fscanf(f, "%d", &val);
		g->a[nr1][nr2] = val;
		g->a[nr2][nr1] = val;
	}
	free(nu1);
	free(nu2);
}

void ping(Graph *g, router r[],FILE *f, FILE *f1){
	int i, nr1, nr2, j, k, l, m1, m2, **D;
	char *ip1 = (char*)malloc(15*sizeof(char)), *ip2 = (char*)malloc(15*sizeof(char));
	fscanf(f, "%s", ip1);
	fscanf(f, "%s", ip2);
	for(i=0;i<g->V;i++){
		for(j=0;j<r[i].nr_pc;j++){
			if(strcmp(r[i].p[j].ip, ip1) == 0){
				if(r[i].p[j].stare == 1)
					nr1 = i;
				else {
					fprintf(f1, "NO\n");
					return ;
				}
			}
			if(strcmp(r[i].p[j].ip, ip2) == 0){
				if(r[i].p[j].stare == 1)
					nr2 = i;
				else{
					fprintf(f1, "NO\n");
					return ;
				}
			}
		}
	}
	if(strlen(r[nr1].nume) == 7)
			m1 = r[nr1].nume[6] - '1';
		else if(strlen(r[nr1].nume) == 8){
			k = r[nr1].nume[6] - '0';
			l = r[nr1].nume[7] - '1';
			m1 = k*10+l;
		}
	if(strlen(r[nr2].nume) == 7)
			m2 = r[nr2].nume[6] - '1';
		else if(strlen(r[nr2].nume) == 8){
			k = r[nr2].nume[6] - '0';
			l = r[nr2].nume[7] - '1';
			m2 = k*10+l;
		}
	D = (int**)malloc(g->V*sizeof(int*));
	for(i=0;i<g->V;i++)
		D[i] = (int*)malloc(g->V*sizeof(int));
	for(i = 0;i < g->V; i++)
		for(j = 0;j < g->V; j++){
			if(g->a[i][j] == 100000)
				D[i][j] = 0;
			else D[i][j] = g->a[i][j];
		}
	for(k = 0; k < g->V; k++)
        for(i = 0; i < g->V; i++)
            for(j = 0; j < g->V; j++)
                if(D[i][k] && D[k][j] && i != j && (D[i][j] > D[i][k] + D[k][j] || !D[i][j]))
                    D[i][j] = D[i][k] + D[k][j];
    if(D[m1][m2] != 0)
    	fprintf(f1, "OK\n");
    else fprintf(f1, "NO\n");
    for(i = 0; i < g->V; i++)
    	free(D[i]);
    free(D);
    free(ip1);
    free(ip2);
}

void sipn(Graph *g, router r[], FILE *f, FILE *f1){
	char *ip = (char*)malloc(15*sizeof(char));
	int i, nr1;
	fscanf(f, "%s", ip);
	for(i=0;i<g->V;i++){
		if(strcmp(r[i].ip, ip) == 0)
			nr1 = i;
	}
	for(i=0;i<g->V;i++)
		if(g->a[nr1][i] != 100000)
			fprintf(f1, "%s ", r[i].ip);
	fprintf(f1, "\n");
	free(ip);
}

void si(Graph *g, router r[], FILE *f, FILE *f1){
	char *ip = (char*)malloc(15*sizeof(char));
	int i, nr1;
	fscanf(f, "%s", ip);
	for(i=0;i<g->V;i++)
		if(strcmp(r[i].ip, ip) == 0)
			nr1 = i;
	for(i = 0;i < r[nr1].nr_pc;i++)
		if(r[nr1].p[i].stare == 1)
			fprintf(f1, "%s ", r[nr1].p[i].ip);
	fprintf(f1, "\n");
	free(ip);
}

int minDistance(int dist[], int sps[], int V){
	int v, min = 100000, min_index;
	for(v = 0;v < V; v++)
		if(sps[v] == 0 && dist[v] <= min){
			min = dist[v];
			min_index = v;
		}
	return min_index;
}

void Dijkstra(Graph *g, router r[], int s, int m2, FILE *f1){
	int i, j , u;
	int *dist = (int*)malloc(g->V*sizeof(int));
	int *sps = (int*)malloc(g->V*sizeof(int));
	int *parent = (int*)malloc(g->V*sizeof(int));
	int *afisare = (int*)malloc(g->V*sizeof(int)), k = 0;
	for(i = 0;i < g->V; i++){
		dist[i] = 100000;
		sps[i] = 0;
		if(g->a[s][i] != 100000) {
			dist[i] = g->a[s][i];
			parent[i] = s; 
		}
	}
	dist[s] = 0;
	sps[s] = 1;
	parent[s] = -1;
	for(j = 0;j < g->V-1; j++){
		u = minDistance(dist, sps, g->V);
		sps[u] = 1;
		for(i = 0;i < g->V; i++){
			if(sps[i] == 0 && g->a[u][i] != 100000 && dist[u] != 100000 && dist[u]+g->a[u][i] < dist[i]){
				dist[i] = dist[u]+g->a[u][i];
				parent[i] = u;
			}

		}
	}
	int x = m2;
	while(x != -1){
		afisare[k] = x;
		k++;
		x = parent[x];
	}
	if(dist[m2] != 100000)	
		for(i = k-1; i >= 0; i--)
			fprintf(f1, "%s ", r[afisare[i]].ip);
	free(dist);
	free(sps);
	free(parent);
	free(afisare);
}

void trace(Graph *g,router r[], FILE *f, FILE *f1){
	int i, j, m1, m2, OK = 1;
	char *ip1 = (char*)malloc(15*sizeof(char)), *ip2 = (char*)malloc(15*sizeof(char));
	fscanf(f, "%s", ip1);
	fscanf(f, "%s", ip2);
	for(i = 0;i < g->V; i++)
		for(j = 0;j < r[i].nr_pc; j++){
			if(strcmp(ip1, r[i].p[j].ip) == 0 )
				m1 = r[i].nr;
			if(strcmp(ip1, r[i].p[j].ip) == 0 && r[i].p[j].stare == 0)
				OK = 0;
			if(strcmp(ip2, r[i].p[j].ip) == 0)
				m2 = r[i].nr;
		    if(strcmp(ip2, r[i].p[j].ip) == 0 && r[i].p[j].stare == 0)
			 	OK = 0;
		}
	if(OK == 1)
		Dijkstra(g, r, m1, m2,f1);
	else fprintf(f1, "\n");
	fprintf(f1, "\n");
	free(ip1);
	free(ip2);
}

void up(Graph *g, router r[], FILE *f){
	char *ip = (char*)malloc(15*sizeof(char));
	int i, j;
	fscanf(f, "%s", ip);
	for(i=0;i<g->V;i++){
		for(j=0;j<r[i].nr_pc;j++)
			if(strcmp(r[i].p[j].ip, ip) == 0)
				r[i].p[j].stare = 1;
	}
	free(ip);
}

void broke(Graph *g, router r[], FILE *f){
	char *ip = (char*)malloc(15*sizeof(char));
	int i, j;
	fscanf(f, "%s", ip);
	for(i=0;i<g->V;i++){
		for(j=0;j<r[i].nr_pc;j++)
			if(strcmp(r[i].p[j].ip, ip) == 0)
				r[i].p[j].stare = 0;
	}
	free(ip);
}

void lc(Graph *g, router r[], FILE *f){
	char *ip1 = (char*)malloc(15*sizeof(char)), *ip2 = (char*)malloc(15*sizeof(char));
	int i, nr1, nr2;
	fscanf(f, "%s", ip1);
	fscanf(f, "%s", ip2);
	for(i = 0;i < g->V;i++){
		if(strcmp(r[i].ip, ip1) == 0)
			nr1 = r[i].nr;
		if(strcmp(r[i].ip, ip2) == 0)
			nr2 = r[i].nr;
	}
	g->a[nr1][nr2] = 100000;
	g->a[nr2][nr1] = 100000;
	free(ip1);
	free(ip2);
}

void add(Graph *g, router r[], FILE *f){
	int i, nr1, nr2, d;
	char *ip1 = (char*)malloc(15*sizeof(char)), *ip2 = (char*)malloc(15*sizeof(char));
	fscanf(f, "%s", ip1);
	fscanf(f, "%s", ip2);
	fscanf(f, "%d", &d);
	for(i=0;i<g->V;i++){
		if(strcmp(r[i].ip, ip1) == 0)
			nr1 = r[i].nr;
		if(strcmp(r[i].ip, ip2) == 0)
			nr2 = r[i].nr;
	}
	g->a[nr1][nr2] = d;
	g->a[nr2][nr1] = d;
	free(ip1);
	free(ip2);
}

void citire2(FILE *f, Graph g, router r[],int c, FILE *f1){
	int i;
	char *s = (char*)malloc(20*sizeof(char));
	for(i = 0;i < c;i++){
		fscanf(f, "%s", s);
		if(strcmp(s, "ping") == 0)
			ping(&g, r, f, f1);
		if(strcmp(s, "sipn") == 0)
			sipn(&g, r, f, f1);
		if(strcmp(s, "si") == 0)
			si(&g, r, f, f1);
	    if(strcmp(s, "trace") == 0)
		 	trace(&g, r, f, f1);
		if(strcmp(s, "up") == 0)
			up(&g, r, f);
		if(strcmp(s, "lc") == 0)
			lc(&g, r, f);
		if(strcmp(s, "broke") == 0)
			broke(&g, r, f);
		if(strcmp(s, "add") == 0)
			add(&g, r, f);
	}
	free(s);
}

int main(int argc, char *argv[]){
	FILE *datein;
	FILE *dateout;
	Graph g;
	router *r;
	int c, i, j;

	datein = fopen(argv[1], "rt");
	dateout = fopen(argv[2], "wt");
	g = create(datein);
	r = (router*)malloc(g.V*sizeof(router));
	citire(&g, r, datein);
	fscanf(datein, "%d", &c);
	citire2(datein, g, r, c, dateout);
	
	for(i = 0; i < g.V; i++)
    	free(g.a[i]);
    free(g.a);
    for(i = 0; i < g.V; i++){
    	free(r[i].nume);
    	free(r[i].ip);
    	for(j = 0; j < r[i].nr_pc; j++){
    		free(r[i].p[j].nume);
    		free(r[i].p[j].ip);
    	}
    	free(r[i].p);
    }
    free(r);
	return 0;
}