//Breadth-First Search
//	Use a queue to track the frontier of vertices between the vertices that have been
//	explored and those have not been explored.
//
//	The first implementation works when visiting a vertex does not depend on its predecessor.
//	The queue here contains the vertices that have not been visited. This means when
//	enqueue an unvisited vertex, we need to check if it is already in the queue.
//	void BreadthFirstSearch1(Graph g, Vertex v)
//	{
//		queue<Vertex> frontier;
//		frontier.enqueue(v);
//		while (!frontier.empty()) {
//			Vertex u = frontire.dequeue();
//			Visit(u);
//			u.Visited = true;
//			for_each (
//				u.AdjacentVertices.begin(), 
//				u.AdjacentVertices.end(), 
//				[&](Vertex & n)->void{
//					if (!n.Visited & !frontier.contains(n)) {
//						frontier.enqueue(n);
//					}
//				}
//			);			
//		}
//	}
//
//	The second implementation works when visiting a vertex depends on its predecessor.
//	The queue here contains the vertices that have been visited.
//	void BreadthFirstSearch2(Graph g, Vertex v)
//	{
//		queue<Vertex> frontier;
//		Visit(null, v);
//		v.Visited = true;
//		frontier.enqueue(v);
//		while (!frontier.empty()) {
//			Vertex u = frontire.dequeue();
//			for_each (
//				u.AdjacentVertices.begin(), 
//				u.AdjacentVertices.end(), 
//				[&](Vertex & n)->void {
//					if (!n.Visited) {
//						Visit(u, n);
//						n.Visited = true;
//						frontier.enqueue(n);
//					}
//				}
//			);			
//		}
//	}

//Depth-First Search
//	Use a stack to track the path from the starting vertex to the current vertex.
//	The stack contains the vertices visited so far.
//
//	void DepthFisrtSearch1(Graph g, Vertex v)
//	{
//		Visit(v);
//		v.Visited = true;
//		for_each (
//			v.AdjacentVertices.begin(),
//			v.AdjacentVertices.end(),
//			[&](Vertex & n)->void {
//				if (!n.Visited) {
//					DepthFirstSearch1(n);
//				}
//			}
//		);
//	}
//
//	void DepthFisrtSearch2(Graph g, Vertex v)
//	{
//		stack<Vertex> path;
//		Visit(v);
//		v.Visited = true;
//		path.push(v);
//		while (!path.empty()) {
//			Vertex c = path.top();
//			Vertex n = c.AdjacentVertices.iterator.next();
//			if (n == null) {
//				path.pop();
//			} else if (!n.Visited) {
//				Visit(n);
//				n.Visited = true;
//				path.push(n);
//			}
//		}
//	}