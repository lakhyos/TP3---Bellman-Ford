
#include <stdio.h>

/* Affectation des arcs avec leurs poids correspondants. */
void affectation_poid(int u, int v, double poid, double d_mini[],
                      int sommet_term_min[])
{
    if (d_mini[v] > d_mini[u] + poid)
    {
        d_mini[v] = d_mini[u] + poid;
        sommet_term_min[v] = u;
    }
}

/* Initialisation des distances avec l'infini (1000000000), sauf pour le
 sommet de depart. */
void initialisation(double d_mini[], int sommet_term_min[], int s, int n)
{
    int i;
    for (i = 1; i <= n; ++i)
    {
        d_mini[i] = 1000000000.0;
        sommet_term_min[i] = 0;
    }
    
    d_mini[s] = 0.0;
}

/* Algorithme de Bellman-Ford. */
int bellman_ford(int sommet[], int sommet_terminal[], int rang_arc_suiv[],
                 double poid[], double d_mini[], int sommet_term_min[],
                 int s, int n)
{
    int u, v, i, j;
    
    initialisation(d_mini, sommet_term_min, s, n);
    
    for (i = 1; i <= n-1; ++i)
    {
        for (u = 1; u <= n; ++u)
        {
            j = sommet[u];
            
            while (j > 0)
            {
                v = sommet_terminal[j];
                affectation_poid(u, v, poid[j], d_mini, sommet_term_min);
                j = rang_arc_suiv[j];
            }
        }
    }
    
    for (u = 1; u <= n; ++u) {
        j = sommet[u];
        
        while (j > 0) {
            v = sommet_terminal[j];
            if (d_mini[v] > d_mini[u] + poid[j])
                return 0;
            j = rang_arc_suiv[j];
        }
    }
    
    return 1;
}

int main(void) {
    int
    sommet[6] /*Tableau des rangs de la premiere apparition d'un sommet
               comme sommet initial dans la liste des arcs*/
    , rang_arc_suiv[11] /*Tableau des rangs de la reapparition suivante
                       d'un sommet comme sommet initiatial d'un arc (0 si
                         la derniere apparition)*/
    , sommet_terminal[11] //Tableau des extremites terminales des arcs.
    , sommet_term_min[6]; /*Tableau des extremites terminales (Dans
                           le graphe minimal)*/
    double
    poid[11] //Tableau des poids
    , d_mini[6]; //Tableau des distances minimales
    int s;
    int i;
    int ok;
    
    /* Le graphe contient les arcs suivants, avec leurs poids:
     (1, 2), poid 6
     (1, 4), poid 7
     (2, 3), poid 5
     (2, 4), poid 8
     (2, 5), poid -4
     (3, 2), poid -2
     (4, 3), poid -3
     (4, 5), poid 9
     (5, 1), poid 2
     (5, 3), poid 7
     */
    
    //Affectation des valeurs:
    
    sommet[1] = 1;
    sommet[2] = 3;//2 apparait comme sommet initial a partir du rang 2
    sommet[3] = 6;
    sommet[4] = 7;
    sommet[5] = 9;
    
    sommet_terminal[1] = 2;
    sommet_terminal[2] = 4;//4 est le sommet terminal de l'arc de rang 2
    sommet_terminal[3] = 3;
    sommet_terminal[4] = 4;
    sommet_terminal[5] = 5;
    sommet_terminal[6] = 2;//2 est le sommet terminal de l'arc de rang 6
    sommet_terminal[7] = 3;
    sommet_terminal[8] = 5;
    sommet_terminal[9] = 1;
    sommet_terminal[10] = 3;
    
    rang_arc_suiv[1] = 2;
    rang_arc_suiv[2] = 0;//c'est la derniere apparition de 2 comme sommet initial
    rang_arc_suiv[3] = 4;
    rang_arc_suiv[4] = 5;
    rang_arc_suiv[5] = 0;
    rang_arc_suiv[6] = 0;
    rang_arc_suiv[7] = 8;//7 reapparait comme sommet initial de l'arc de rang 8
    rang_arc_suiv[8] = 0;
    rang_arc_suiv[9] = 10;
    rang_arc_suiv[10] = 0;
    
    poid[1] = 6.0;
    poid[2] = 7.0;
    poid[3] = 5.0;
    poid[4] = 8.0;
    poid[5] = -4.0;
    poid[6] = -2.0;
    poid[7] = -3.0;
    poid[8] = 9.0;
    poid[9] = 2.0;
    poid[10] = 7.0;

    
    printf("Entrer le sommet source: ");
    scanf("%d", &s);
    
    ok = bellman_ford(sommet, sommet_terminal, rang_arc_suiv, poid, d_mini,
                      sommet_term_min, s, 5);
    
    printf("D'apres l'algorithme de Bellman-Ford, on a: ");
    printf("%d\n\n", ok);
    
    for (i = 1; i <= 5; ++i)
        printf("(%d,%d,%f)\n", i, sommet_term_min[i], d_mini[i]);
    
    return 0;
}

/* Differentes traces:
 
 Entrer le sommet source: 1
 D'apres l'algorithme de Bellman-Ford, on a: 1

 (1,0,0.000000)
 (2,3,2.000000)
 (3,4,4.000000)
 (4,1,7.000000)
 (5,2,-2.000000)
 
 Entrer le sommet source: 2
 D'apres l'algorithme de Bellman-Ford, on a: 1
 
 (1,5,-2.000000)
 (2,0,0.000000)
 (3,4,2.000000)
 (4,1,5.000000)
 (5,2,-4.000000)

 Entrer le sommet source: 3
 D'apres l'algorithme de Bellman-Ford, on a: 1
 
 (1,5,-4.000000)
 (2,3,-2.000000)
 (3,0,0.000000)
 (4,1,3.000000)
 (5,2,-6.000000)
 
 Entrer le sommet source: 4
 D'apres l'algorithme de Bellman-Ford, on a: 1
 
 (1,5,-7.000000)
 (2,3,-5.000000)
 (3,4,-3.000000)
 (4,0,0.000000)
 (5,2,-9.000000)
 
 Entrer le sommet source: 5
 D'apres l'algorithme de Bellman-Ford, on a: 1
 
 (1,5,2.000000)
 (2,3,4.000000)
 (3,4,6.000000)
 (4,1,9.000000)
 (5,0,0.000000)


 
*/