const fs = require('fs');
var Edges = []
var Nodes = []

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

function introduceNewNode(n1, n2) {
    let newNode = 1000 * (n1 + n2)
    Nodes = Nodes.filter(x => x != n1 && x != n2).concat([newNode])
    Edges = Edges.map(x => {
        return x.map(y => { return (y == n1 || y == n2) ? newNode : y })
    })}

function mergedNodes(edge) {
    Edges = Edges.filter(x => !isEdgeOfTheNodes(edge[0], edge[1], x))
    return introduceNewNode(edge[0], edge[1])
}

function contract() {
    if (Nodes.length <= 2) return
    let edge = pickEdge(Edges)
    mergedNodes(edge)
    contract()
}

function doTheStuff() {
    let graph = genGraph()
    let initialNodes = graph.nodes
    let initialEdges = graph.edges
    console.log(graph)
    let minCut = initialEdges.length
    for (i = 0; i < 1; i++) {
        Edges = initialEdges
        Nodes = initialNodes
        contract()
        if (Edges.length < minCut)
            minCut = Edges.length
    }
    console.log(minCut)
}

doTheStuff()
