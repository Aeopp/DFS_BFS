#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
using namespace std;

struct node;
struct edge
{
public:
	node* dst;
	edge(node* param) :dst(param) {};
};
struct node
{
	string name;
	bool bvisit = false;
	std::vector<edge*> edges;
	inline void func()
	{
		cout << name << endl;
	}
public:
	node(string param) :name(param) { };
};

namespace GraphSearch
{
	inline void Visit(node* s)
	{
		 s->func();
	}
	inline void ArrayVersion(node* t,node* s)
	{
		cout << "\n출발한 정점 ";
		Visit(t);
		cout << "\n도착한 정점 ";
		Visit(s);
		s->bvisit = true;
		std::vector<node*> visiter;
		for(auto& e:s->edges)
		{
			  if ( e->dst->bvisit == false)
			  {
				  e->dst->bvisit = true;
				  visiter.push_back(e->dst);
			  }
		}
		for(const auto& e: visiter)
		{
			ArrayVersion(s,e);
		}
	}
	// 시작 노드부터 큐에 푸시한다.
	// 노드의 연결된 노드를 
	void BFSQueue(node* param)
	{
		param->func();
		static queue<node*> q;
		for(const auto& e : param->edges)
		{
			if (e->dst->bvisit == false)
			{
				e->dst->bvisit=true;
				q.push(e->dst);
			}
		}
		if (q.empty())return;
		while(!q.empty())
		{
			
			auto t = q.front();
			q.pop();
			BFSQueue(t);
		}
		return;
	}
	// DFS 구현
	// 리턴 조건 : 스택이 비어있고 ( 돌아갈곳이 없고 , 지나갈 간선도 없을때)
	// 자기자신의 방문은 True 로 바로 만들어준다.
	// 호출자의 간선 배열을 순회한다.
	// 간선 배열에서 방문되지 않는 엘리먼트를 찾았다면 방문 true 로 마킹하고
	// // 자기 자신을 스택에 푸시하고 해당 엘리먼트의 DFS 를 호출한다.
	// 배열에서 방문 할수있는 엘리먼트가 없다면 스택이 비어있는지 검사한다.
	// 스택이 비어있지 않다면 스택에서 하나 Top 의 BFS를 호출한다.
	// 스택이 비어있다면 함수를 종료한다.
	
	void DFSStack(node* G)
	{
		G->func();

		static stack<node*> St;
		G->bvisit = true;
		for(auto& E:G->edges)
		{
			if(E->dst->bvisit==false)
			{
				St.push(G);
				DFSStack(E->dst);
				return;
			}
		}
		if (St.empty())return;
		auto Call = St.top();
		St.pop();
		DFSStack(Call);
	}
	bool IsAllVisit(node* G,std::vector<node*>& T)
	{
		DFSStack(G);
		for (const auto& E : T)
		if (E->bvisit == false)return false;
		
		return true;
	}
}
// ArrayVersion 를 어떻게 구현 할 것인가?
// void temp(node* t)
// 나는 방문했다고 표시한다.
// 큐를 준비한다.
// 에지들을 관리하는 배열을 순회해야한다.
// 에지들을 관리하는 배열의 노드를 살펴보고 그 노드의 방문했다는 표식이 없다면
// 방문했다는 표식을 남겨버린다(방문하는 함수를 먼저 호출해선 안된다 미리 표식만 남긴다)
// 방문했다는 표식이 남아있는 노드들의 배열을 순회하며 방문함수를 호출한다.
// 방문 함수 시작
// 에지 배열을 순회하며 해당 배열의 노드의 방문 표시가 없다면 트루로 미리 다 만든다
// 트루로 미리 만든 배열을 순회하며 함수를 호출한다.
// 함수를 호출한다.
// 로그 펑션을 호출한다. // 디버깅
// 큐가 비어있다면 탐색이 종료된것이니 탐색종료를 한다.
// 큐가 비어있지 않다면 큐에서 하나 꺼내서 자신의 모든 간선에 연결된 정점을 호출한다.
// 여기서 그 정점의 방문했던 노드라면 호출하지 않는다.
// 이 작업을 큐가 비어있을때 까지 반복한다.
//
// 
//template <typename T,typename G>
//void pushgraph(std::vector<G*>& Target,T* s) {
//	cout << "das";
//	Target.push_back(s);
//}
//template <typename G,typename T, typename... Ts>
//void pushgraph(std::vector<G*>& Target, T* s,Ts*... ss) {
//	pushgraph(Target, ss...);
//}
int main()
{
	/*node* A = new node("A");
	node* B= new node("B");
	node* C= new node("C");
	node* D= new node("D");
	node* E= new node("E");
	node* Z = new node("Z");
	
	A->edges.emplace_back(&edge(B));
	A->edges.emplace_back(&edge(C));
	A->edges.emplace_back(&edge(E));
	A->edges.emplace_back(&edge(Z));
	 
	B->edges.emplace_back(&edge(A));
	B->edges.emplace_back(&edge(C));
	
	C->edges.emplace_back(&edge(A));
	C->edges.emplace_back(&edge(B));
	C->edges.emplace_back(&edge(E));
	 					  
	D->edges.emplace_back(&edge(E));
	D->edges.emplace_back(&edge(Z));
	
	E->edges.emplace_back(&edge(A));
	E->edges.emplace_back(&edge(D));
	E->edges.emplace_back(&edge(C));
	
	Z->edges.emplace_back(&edge(A));
	Z->edges.emplace_back(&edge(D));

	 GraphSearch::BFSQueue(Z);*/
	
//////////////////////////	/*auto MakeNode = [](string param)->node*
///{return new node(param); };
//////////////////////////	node* A = MakeNode("A");
//////////////////////////	node* B = MakeNode("B");
//////////////////////////	node* C = MakeNode("C");
//////////////////////////	node* D = MakeNode("D");
//////////////////////////	node* E = MakeNode("E");
//////////////////////////	node* F = MakeNode("F");
//////////////////////////	node* G = MakeNode("G");
//////////////////////////	node* H = MakeNode("H");*/
//////////////////////////	/*auto MakeEdge = [](node* lhs, node* rhs)
//////////////////////////	{
//////////////////////////		lhs->edges.emplace_back(&edge(rhs));
//////////////////////////		rhs->edges.emplace_back(&edge(lhs));
//////////////////////////	};*/
//////////////////////////	//MakeEdge(A, B);
////////////////////////////MakeEdge(A, G);
////////////////////////////MakeEdge(B,C);
////////////////////////////MakeEdge(D, B);
////////////////////////////MakeEdge(D, G);
////////////////////////////MakeEdge(H, G);
////////////////////////////MakeEdge(E, F);
////////////////////////////MakeEdge(E, D);
	
	node* A= new node("A");
	node* B= new node("B");
	node* C= new node("C");
	node* D= new node("D");
	node* E= new node("E");
	node* F= new node("F");
	node* G = new node("G");
	node* H= new node("H");
	
	A->edges.emplace_back(&edge(B));
	A->edges.emplace_back(&edge(G));

	B->edges.emplace_back(&edge(A));
	B->edges.emplace_back(&edge(C));
	B->edges.emplace_back(&edge(D));

	C->edges.emplace_back(&edge(B));
	
	D->edges.emplace_back(&edge(B));
	D->edges.emplace_back(&edge(E));

	E->edges.emplace_back(&edge(D));
	E->edges.emplace_back(&edge(F));

	G->edges.emplace_back(&edge(A));
	G->edges.emplace_back(&edge(H));
	H->edges.emplace_back(&edge(G));

	F->edges.emplace_back(&edge(E));

	// GraphSearch::DFSStack(A);
	
	std::vector<node*> Graphs = { A, B, C, D, E, F, G, H };

	

};
