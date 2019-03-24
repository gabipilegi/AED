const fs = require('fs');

function swap(input, i, j) {
    let aux = input[i]
    input[i] = input[j]
    input[j] = aux
}

function partition(input, l, r) {

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

function compare(a, b) {
    if (a.value > b.value) return 1;
    if (a.value < b.value) return -1;
    return 0;
}

function medianOfThreePivod(input, l, r) {
    let positions = [{ index: l, value: input[l] },
    { index: r, value: input[r] }]

    if (input.length > 2) {
        let mid = Math.floor((r - l) / 2)
        positions.push({ index: mid, value: input[mid] })
    }
    return positions.sort(compare)[1].index
}

function choosePivot(strategy, input, l, r) {
    switch (strategy) {
        case 1: swap(input, l, r)
            break
        case 2: swap(input, l, medianOfThreePivod(input, l, r))
    }
}

function sortAndCountComparisons(input, l, r, strategy) {
    if (r == l) return 0
    choosePivot(strategy, input, l, r)
    let i = partition(input, l, r)
    let levelComp = (r - l)
    let leftComp = sortAndCountComparisons(input, l, Math.max(l, i - 1), strategy)
    let rightComp = sortAndCountComparisons(input, Math.min(r, i + 1), r, strategy)
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
    return sortAndCountComparisons(input, 0, input.length - 1, 2)
}

console.log(doTheStuff())

//0: 162085
//1: 164123
//2: 159894