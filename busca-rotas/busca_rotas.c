#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "lista_adj.h"

#define RAD(a) ((a * M_PI) / 180.0)


Coordinate coordinate(double latitude, double longitude){
  Coordinate c;
  c.latitude = latitude;
  c.longitude = longitude;
  return c;
}

Vector vector(Coordinate c){
  Vector v;
  double lat = RAD(c.latitude);
  double lon = RAD(c.longitude);
  v.x = cos(lat) * sin(lon);
  v.y = sin(lat);
  v.z = cos(lat) * cos(lon);
  return v;
}

double dot(Vector v1, Vector v2){
  return  v1.x * v2.x +
    v1.y * v2.y + 
    v1.z * v2.z
  ;
}

int distance(Coordinate c1, Coordinate c2, double radius){

  Vector p1 = vector(c1);
  Vector p2 = vector(c2);

  double angle = acos(dot(p1, p2));
  double distance = angle * radius;
    
  return lrint(distance);
}

/*********************das aulas*************************************/
Grafo * cria_grafo(int max_v){
  Grafo * g = (Grafo *) malloc (sizeof(Grafo));
  g->vertices = (Vertice *) malloc (max_v * sizeof(Vertice));
  g->nv = 0;
  g->na = 0;

  return g;
}

void adiciona_vertice(Grafo*g,int id,char* nome,char* cidade,char* pais,char* IATA,double latitude,double longitude){
  g->vertices[g->nv].id = id;
  g->vertices[g->nv].nome = nome;
  g->vertices[g->nv].cidade = cidade;
  g->vertices[g->nv].pais = pais;
  strcpy (g->vertices[g->nv].IATA,IATA); 
  g->vertices[g->nv].latitude = latitude;
  g->vertices[g->nv].longitude = longitude;
  g->vertices[g->nv].pai = NULL;
  g->vertices[g->nv].prox = NULL;
  g->vertices[g->nv].arestas = NULL;
  g->vertices[g->nv].cor = BRANCO;
  g->nv++;
}


Vertice * pega_vertice(Grafo * g, int id){
  
  int i;

  

  for(i = 0; i < g->nv; i++){

    if(g->vertices[i].id == id){
    
       return &g->vertices[i];
    }
  }

  return NULL;
}



Aresta* pega_aresta(Grafo * g,int u_id,int v_id){

  int achou = 0;
  Vertice * u = pega_vertice(g,u_id);
  Aresta * a = u->arestas;
  
  while(a && achou ==0){    
    if(a->dst->id == v_id){     
      return(a);
    }

    a = a->prox;
  }

  if(!achou){
    
    return(NULL);
  }

}


int verifica_aresta(Grafo * g,int u_id,int v_id){

  int achou = 0;
  Vertice * u = pega_vertice(g,u_id);
  Aresta * a = u->arestas;
  
  while(a && achou ==0){    
    if(a->dst->id == v_id){     
      return(1);
    }

    a = a->prox;
  }

  if(!achou){
    
    return(0);
  }

}

void adiciona_aresta(Grafo * g, int u_id, int v_id){
  int achou = verifica_aresta(g,u_id,v_id);
  if(achou == 0){ 
  Vertice * u = pega_vertice(g, u_id);
  Vertice * v = pega_vertice(g, v_id);

  Aresta * a = (Aresta *) malloc (sizeof(Aresta));

  a->dst = v;
  a->prox = u->arestas;
  u->arestas = a;

  g->na++;
   }
}

void imprime_grafo(Grafo * g){

  int i;
  Vertice v;
  Aresta * a;

  printf("O grafo possui %d vertices e %d arestas:\n", g->nv, g->na);

  for(i = 0; i < g->nv; i++){
  
    v = g->vertices[i];
    printf("%d:", v.cor);

    a = v.arestas;
    while(a){
    
      printf(" %d", a->dst->id);
      a = a->prox;
    }

    printf("\n");
  }

  printf("\n");
}
/*********************das aulas*************************************/
void entra_fila(Fila * f, Vertice * v){
  if(f->fim) f->fim->prox = v;
  else f->inicio = v;
  f->fim = v;
}
 
Vertice * sai_fila(Fila * f){
  Vertice * resposta;
  
  resposta = f->inicio;
  f->inicio = f->inicio->prox;
  
  if(!f->inicio)f->fim = NULL;
  return resposta;
}



//ep serio aqui meu, na seriedade



void bubble(Grafo* g,int corte )
{
  int inicio= corte;   
  int i;
  int j;
  Vertice aux;
  int k = g->nv - 1 ;

  for(i = inicio; i < g->nv; i++)
  {
     for(j = inicio; j < k; j++)
     {
        if(g->vertices[j].distancia > g->vertices[j+1].distancia)
        {
        aux = g->vertices[j];
        g->vertices[j] = g->vertices[j+1];
        g->vertices[j+1] =aux;
        }
     }
     k--;
  }
}



void criaVetorVertices(Grafo*g){
     
    FILE* aeroportos = fopen("airports.dat","r");
    char str[160];
    char * delim = ",";   
    int cont=0;
    char*nome;
    char*cidade;
    char*pais;
    char IATA[100];
    double latitude=0;
    double longitude=0;
        
    while(feof(aeroportos) == 0 ){     
                           
    char*result = fgets(str,160,aeroportos);
        if(result){
            int ehValida=1;       
            
            //id 
            char* token = strtok(str, delim);            
            int id= atoi(token);
            
            //nome
            token = strtok(NULL,delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }else{
            nome = malloc(strlen(token)*2);
            strcpy(nome,token);      
            }
            //cidade            
            token = strtok(NULL,delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }else{
            cidade = malloc(strlen(token)*2);
            strcpy(cidade,token);
            }
            
         
            
            //pais
            token = strtok(NULL,delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }else{
            pais = malloc(strlen(token)*2);
            strcpy(pais,token);      
            }            
                   
            //IATA
            token = strtok(NULL,delim); 
           
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }else{
            
            strcpy(IATA,token);      
            }
            
            
            //inutil
            token=strtok(NULL,delim); 
            
            //latitude
            token = strtok(NULL,delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }else{
            latitude = (double)atof(token);
            
            }
            
            
            //longitude
            token = strtok(NULL,delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }else{           
            longitude = (double)atof(token);                     
            }            
            if(ehValida>0){           
            //printf("%d %s %s %s %s %d %d \n ",id,nome,cidade,pais,IATA,latitude,longitude);
            adiciona_vertice(g,id,nome,cidade,pais,IATA,latitude,longitude);
            }
            cont = cont+ehValida;
        } 
    }
    
    fclose(aeroportos);
     
}

int contaVertice(char*entrada){
    
    FILE* aeroportos = fopen("airports.dat","r");
    char str[160];
    char * delim = ",";   
    int cont=0;
        
    while(feof(aeroportos) == 0 ){     
                           
    char*result = fgets(str,160,aeroportos);
        if(result){
            int ehValida=1;       
            //id 
            char* token = strtok(str, delim);            
            
            //nome
            token = strtok(NULL,delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }
            //cidade            
            token = strtok(NULL,delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }
            
         
            
            //pais
            token = strtok(NULL,delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }            
                   
            //IATA
            token = strtok(NULL,delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }
            
            
            //inutil
            token=strtok(NULL,delim); 
            
            //latitude
            token = strtok(NULL,delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }
            
            
            //longitude
            token = strtok(NULL,delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
            ehValida=0;
            }            
            cont = cont+ehValida;
        } 
    }
    
    fclose(aeroportos);
    return(cont);
}

void criaArestas(Grafo* g,char* arst){
    FILE* rotas = fopen(arst,"r");
    char str[160];
    char * delim = ",";   
    char*token;
    int cont=0;
    int origem=0;
    int destino=0; 
     
    while(feof(rotas) == 0 ){
        char*result = fgets(str,160,rotas);
        
        if(result){
            int ehValida=1;          
            //airline INUTIL
            token= strtok(str, delim);   
            //airline id INUTL
            token= strtok(NULL, delim);
            //source IATA INUTIL
            token= strtok(NULL, delim);
            //source ID
            token= strtok(NULL, delim); 
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
                ehValida=0;
            }else{
              origem= atoi(token);              
            }            
            //destination IATA INUTL
            token= strtok(NULL, delim);
            //Destination ID     
            token= strtok(NULL, delim);  
            if(strcmp("\\N", token) == 0 || strcmp("\"\"", token) == 0){
                ehValida=0;
            }else{
               destino= atoi(token);              
            }      
            if(ehValida>0){  
                             
                  
                 // printf("%d - %d \n",origem,destino);                                                    
                  adiciona_aresta(g,origem,destino);                    
                  cont=cont+ehValida;
                
                
            }
            
        } 
    }
    fclose(rotas);                          
}

void busca_largura(Grafo*g,int id_origem){
  int i;
  //pinta vertices de branco e seta seus pais como null
  for(i = 0; i < g->nv; i++){
    g->vertices[i].cor = BRANCO;
    g->vertices[i].nescalas = 9999;
    g->vertices[i].pai = NULL;    
  }
  
  Vertice* origem = pega_vertice(g,id_origem);

  
  //pinta o inicio de cinza e seta sua distancia como 0
  origem->cor = CINZA;
  origem->nescalas = 0;
  origem->pai = NULL;
  
  //Inicializa a fila
  Fila * f = (Fila*) malloc(sizeof(Fila));
  f->inicio = NULL;
  f->fim = NULL;
  

  //ComeÃ§a de fato a busca, colorindo os vÃ©rtices
  entra_fila(f, origem);
  
  Vertice * u;
  Vertice * v;
  Aresta * a;
  

  while(f->inicio){
           
    Vertice* u = sai_fila(f);
   
    Aresta* a = u->arestas;   
    while(a){
                 
      v = a->dst;
      if(v->cor == BRANCO){
        v->cor = CINZA;
        //nescalas é colocado no vtc
        //distancia é colocada no vtc
        //distancia é colocada na arsta
        double earth_radius =  6371.009;
        Coordinate uCoor = coordinate(u->latitude,u->longitude);
        Coordinate vCoor = coordinate(v->latitude,v->longitude);        
          int distancia =distance(uCoor,vCoor,earth_radius);      
                v->nescalas= u->nescalas+1;
                v->distancia= u->distancia+ distancia;
              
        
                v->pai = u;
        entra_fila(f,v);
      }
      a = a->prox;
    }
    u->cor = PRETO;
  }
  



}


int extrai_min(Grafo* g){
   int min;
   int i;
   int id_min;
   min = 999999;
   
   
   for(i=0;i<g->nv;i++){
       if((g->vertices[i].distancia <= min) && (g->vertices[i].cor!=PRETO)){
          min = g->vertices[i].distancia;          
          id_min= g->vertices[i].id;                                    
           
       }                     
   }
 
   return(id_min);
}    

    
                        
void relaxa(Grafo*g,Vertice*u,Vertice*v){
    
    double earth_radius =  6371.009;
    Coordinate uCoor = coordinate(u->latitude,u->longitude);
    Coordinate vCoor = coordinate(v->latitude,v->longitude);     
    
    int origem_u_v = u->distancia + distance(uCoor,vCoor,earth_radius);
    
    // se a distancia de v for maior que distancia de u mais peso da aresta uv
    if(v->distancia > origem_u_v){     
    //distancia de v = distancia de u + pesoaresta
       v->distancia = origem_u_v;   
       v->nescalas = u->nescalas+1;    
       //v->pai= u
       v->pai = u;
     
    }
   
}

Dijkstra(Grafo* g,int origem){
      Vertice* raiz = pega_vertice(g,origem);
      //inicializa grafo e raiz
        int i;
        for(i=0;i<g->nv;i++){
        g->vertices[i].distancia=999999;   
        g->vertices[i].pai=NULL;  
        g->vertices[i].cor=BRANCO;
        }
        
        raiz->distancia = 0;
     //-------------------------   
        
      //corte = vertices analizados
      int corte = 0;
      
      //enquanto houver vertices nao descobertos
      while(corte < g->nv){
         
         int  id_u = extrai_min(g);
         Vertice* u = pega_vertice(g,id_u);   
        
          
         //para cada v na adjacencia de u
         Aresta* aux = u->arestas;     
        
         while(aux){
             Vertice*v = aux->dst;  
             
             relaxa(g,u,v);
             aux= aux->prox;
         }
         
         u->cor= PRETO; 
         corte= corte+1;        
      }                             
}

int pega_id(Grafo*g,char* cod){
int i;


  for(i=0;i<g->nv;i++){           
     char result[100];
     char* iata;
     strcpy(result,g->vertices[i].IATA);
     strtok(result,"\"");
     iata= strtok(result,"\"");      
                  
     if(strcmp(iata,cod) ==0 ){
        int id=g->vertices[i].id;  
                               
        return(id);
     } 
  }        

return (-1);
}

void imprime_rota(Vertice*dest,FILE**saida){
 if(dest){
     imprime_rota(dest->pai,saida);
     char result[100];
     char* iata;
     strcpy(result,dest->IATA);
     strtok(result,"\"");
     iata= strtok(result,"\""); 
     printf(" %s ",iata);
     fprintf(*saida,"%s ",iata);
 }

}


int main(int argc, char *argv[])
{     
  //abrir o txt referente ao argumento 1(entrada)  
  FILE* entrada = fopen(argv[1],"r");         
  //se o arqivo for válido
  if(entrada){
      printf("\nArquivo aberto com sucesso\n");
      
      char vtcs[100]; 
      char arst[100];
      char act[100];
      char orgm[100];    
      char ndest[4];
      //char destinos[ndest];
        
      
      //lerndo a entrada
     fscanf(entrada,"%s",vtcs);
     fscanf(entrada,"%s",arst);
     fscanf(entrada,"%s",act);
     fscanf(entrada,"%s",orgm);       
     fscanf(entrada,"%s",ndest);
     int ndestinos = atoi(ndest);
     char* destinos[ndestinos];  
     int i;
     char d[100];  
     char aspa[1]= "\"";
     for(i=0;i<ndestinos;i++){
         char*result;   
                       
         fscanf(entrada,"%s",d);
                 
         destinos[i] = malloc(200);
         strcpy(destinos[i],d);
         
     }  
    
     
      int nVert= contaVertice(vtcs);
      Grafo* g = cria_grafo(nVert);
      criaVetorVertices(g);
      criaArestas(g,arst);
      
      
         
      int vtcsdest[ndestinos]; 
       
      for(i=0;i<ndestinos;i++){
      int id= pega_id(g,destinos[i]);
      if(id!= -1){
              vtcsdest[i] =id;
      }else{
              vtcsdest[i]= -42;
      }
        
      } 
      
      int id_origem = pega_id(g,orgm);
     
     if(strcmp(act,"ESCALAS")==0){
         busca_largura(g,pega_id(g,orgm));
          
         FILE* saida_escalas =fopen("saida_escalas.txt","w");
         //printa resultados 
         printf("-------------------------------------------------------------------------------\n");
         printf("Origem:%s | critério:%s | Total de vértices:%d | Total de arestas:%d\n",orgm,act,g->nv,g->na); 
         printf("-------------------------------------------------------------------------------\n");
        
         fprintf(saida_escalas,"%s %s %d %d \n",orgm,act,g->nv,g->na);
        
         for(i=0;i<ndestinos;i++){          
          int id_dest = vtcsdest[i];
          Vertice*dest_i = pega_vertice(g,id_dest);   
          if(dest_i){
          printf("Destino:%s : ",dest_i->IATA); 
          fprintf(saida_escalas,"%s ",dest_i->IATA);
          }
          if(dest_i!=NULL && dest_i->pai!=NULL){
                 
                        
              printf("Aeroportos:%d : ",dest_i->nescalas+1);
              printf("Distancia:%d : ",dest_i->distancia);
              fprintf(saida_escalas,"%d %d ",dest_i->nescalas+1,dest_i->distancia);
              
              printf("rota: ");
              if(dest_i->pai){
              imprime_rota(dest_i,&saida_escalas);
              fprintf(saida_escalas,"\n");
              }else{
                
              }
              printf("\n");
              
          }else{
              printf("NAO EXISTE CAMINHO\n");
              fprintf(saida_escalas,"NAO EXISTE CAMINHO\n");
              }                
          } 
    
    fclose(saida_escalas);
    }
     
      
    if(strcmp(act,"DISTANCIA")==0){
        Dijkstra(g,id_origem);
        printf("-------------------------------------------------------------------------------\n");
        printf("Origem:%s | critério:%s | Total de vértices:%d | Total de arestas:%d\n",orgm,act,g->nv,g->na); 
        printf("-------------------------------------------------------------------------------\n");
        
        FILE* saida_distancia =fopen("saida_distancia.txt","w");
        fprintf(saida_distancia,"%s %s %d %d \n",orgm,act,g->nv,g->na);
        
        for(i=0;i<ndestinos;i++){          
              int iDest = vtcsdest[i];
              Vertice* DestI = pega_vertice(g,iDest); 
              
              if(DestI){
              printf("Destino:%s : ",DestI->IATA);   
              fprintf(saida_distancia,"%s ",DestI->IATA);             
              }
              if(DestI!=NULL && DestI->distancia != 999999){
                         
                  printf("Aeroportos:%d : ",DestI->nescalas+1);
                  printf("Distancia:%d : ",DestI->distancia);
                  fprintf(saida_distancia,"%d %d ",DestI->nescalas+1,DestI->distancia);
                  printf("rota:");
                  if(DestI->pai){
                   imprime_rota(DestI,&saida_distancia);
                   printf("\n");
                   fprintf(saida_distancia,"\n");
                  }
                 
              }else{
                  printf("NAO EXISTE CAMINHO\n");
                  fprintf(saida_distancia,"NAO EXISTE CAMINHO\n");
                  }                
              
        }
        fclose(saida_distancia);
    }  
      
      
      
      
      
  }else{
      printf("arquivo de entrada não existe");  
  }
  system("PAUSE");  
  return 0;
}



