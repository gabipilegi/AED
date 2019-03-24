const fs = require('fs');


function swap(input, i, j) {
    let aux = input[i]
    input[i] = input[j]
    input[j] = aux
}

function partition(input, l, r) {
    console.log(input.slice(l, r + 1))
    if (r == l + 1 && input[l] < input[r]) return l
    let pivot = input[l]
    let i = l + 1
    for (j = l + 1; j <= r; j++) {
        if (input[j] < pivot) {
            swap(input, i, j)
            i++
        }
    }
    let switchPosition = (Math.min(i - 1, r))
    swap(input, l, switchPosition)
    return switchPosition
}

function sort(input, l, r) {
    if (r == l) return 0
    let i = partition(input, l, r)
    let levelComp = (r - l)
    let leftComp = sort(input, l, Math.max(l, i - 1))
    let rightComp = sort(input, Math.min(r, i + 1), r)
    return levelComp + leftComp + rightComp
}
function getInput() {
    let rawInput = fs.readFileSync('quicksort.txt', 'utf8')
    let listStr = rawInput.split("\n");
    listStr.splice(listStr.length - 1, 1)

    return listInt = listStr.map(x => parseInt(x))
}

function doTheStuff() {
    let input = getInput()
    return sort(input, 0, input.length - 1)
}
//console.log(partition([5,2,1],0,2))
console.log(doTheStuff())