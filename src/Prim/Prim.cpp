#include "Prim.h"
#include <queue>



Prim::Prim(ListAdj* list){
	
	this->listadj = list;

}

void Prim::algorithm(){
	
	int qVertices = listadj->getSize();
	std::vector < NodeData >vertices(qVertices);
	// O valor armazenado no vetor indicar se o indice está ou não na queue
	// se verticesInQueue[1] = false, logo o vertice 1 não está na queue
	std::vector < bool > verticesInQueue(qVertices);

	for(int i = 0; i < qVertices; i++){
		vertices[i].vertice = i;
		vertices[i].chave = 9999999;
		vertices[i].pai = NULL;
		verticesInQueue[i] = true;

	}
	// Vamos iniciar como a raiz sendo sempre zero inicialmente
	vertices[0].chave = 0;

	// Agora devemos inicializar uma fila de prioridade baseada no valor da chave
	// Vamos iniciar a fila do menor para o maior valor em ordem nao decrescente
	auto cmp = [](const NodeData &a, const NodeData &b){
			
		return a.chave >= b.chave;
	};

	std::priority_queue<NodeData,std::vector<NodeData>, decltype(cmp) > queueVertices(cmp);

	for(int i = 0; i < qVertices; i++){
		queueVertices.push(vertices[i]);
	}
	
	while(!queueVertices.empty()){
		
		NodeData nodeData = queueVertices.top();
		// Vamos agora percorrer todos os nos adjacentes a esse vertice
		Node* nodeU = listadj->getNode(nodeData.vertice);
		Node* nodeAux = nodeU->adj; //Acessa o primeiro adjacente
		
		while(nodeAux != NULL){
			
			int adjVertice = nodeAux->vertice;
			int peso = nodeAux->peso;
			int chave = vertices[adjVertice].chave;
			
			if(verticesInQueue[adjVertice] and peso < chave){
				vertices[adjVertice].pai = nodeU;
				vertices[adjVertice].chave = peso;
				queueVertices.push(vertices[adjVertice]); //Adiciona o vertice novo na priority queue
			}
			nodeAux = nodeAux->adj;
			
		}
		
		queueVertices.pop();
	
	}
}