const fs = require('fs');


function readInput() {
    let rawInput = fs.readFileSync('input', 'utf8')
    let listStr = rawInput.split("\n");
    listStr.splice(listStr.length - 1, 1)
    return listStr;
}

function computeLine(strLine) {
    let node = parseInt(strLine.substring(0, 1))
    let edges = new Array()
    strLine
        .substring(2, strLine.length - 1)
        .split(",")
        .map(x => edges.push([node, parseInt(x)]))
    return { node: node, edges: edges }
}

function genGraph() {
    let graph = { nodes: [], edges: [] }
    readInput().map(x => {
        let result = computeLine(x);
        graph.nodes.push(result.node)
        result.edges.map(x => graph.edges.push(x));
    })
    return graph
}

function pickEdge(edges) {
    return edges[Math.floor(Math.random() * (edges.length - 1))]
}

function isEdgeOfTheNodes(n1, n2, edge) {
    return (edge[0] == n1 && edge[1] == n2) || (edge[0] == n2 && edge[1] == n1)
}

function introduceNewNode(graph, n1, n2) {
    let newNode = 1000 * (n1 + n2)
    let newNodeList = graph.nodes.filter(x => x != n1 && x != n2).concat([newNode])
    let newEdgeList = graph.edges.map(x => {
        return x.map(y => { return (y == n1 || y == n2) ? newNode : y })
    })
    return {
        nodes: newNodeList,
        edges: newEdgeList
    }
}

function mergedNodes(graph, edge) {
    let graphWithFilteredEdgeList = {
        nodes: graph.nodes,
        edges: graph.edges.filter(x => !isEdgeOfTheNodes(edge[0], edge[1], x))
    }
    return introduceNewNode(graphWithFilteredEdgeList, edge[0], edge[1])
}

function contract(graph) {
    if (graph.nodes.length <= 2) return graph
    let edge = pickEdge(graph.edges)
    let contractedGraph = mergedNodes(graph, edge)
    return contract(contractedGraph)
}

function doTheStuff() {
    let graph = genGraph()
    
    let minCutGraph = graph
    for (i = 0; i < 2; i++) {
        let contractedGraph = contract(graph)
        if (contractedGraph.edges.length < minCutGraph.edges.length)
            minCutGraph = contractedGraph
    }
    console.log(minCutGraph.edges.length)
}

doTheStuff()
