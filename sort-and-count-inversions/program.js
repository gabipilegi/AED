const fs = require('fs');

function mergeAndCount(a, b, inversions) {
    let c = []
    let i = 0
    let j = 0

    for (k = 0; k < (a.length + b.length); k++) {
        if (!b[j] || a[i] <= b[j]) {
            c.push(a[i])
            i++
        } else {
            inversions = inversions + (a.length - i)
            c.push(b[j])
            j++
        }
    }
    return {
        sortedArray: c,
        inversions: inversions
    }
}

function sortAndCount(input) {
    if (input.length == 1) {
        return {
            sortedArray: input,
            inversions: 0
        }
    }

    let half = input.length / 2
    let leftHalfResult = sortAndCount(input.slice(0, half))
    let rightHalfResult = sortAndCount(input.slice(half, input.length))
    return mergeAndCount(leftHalfResult.sortedArray, rightHalfResult.sortedArray, leftHalfResult.inversions + rightHalfResult.inversions)
}

function getInput() {
    let rawInput = fs.readFileSync('input.txt', 'utf8')
    let listStr = rawInput.split("\n");
    listStr.splice(listStr.length - 1, 1)
    return listInt = listStr.map(x => parseInt(x))
}

function doTheStuff() {
    let input = getInput()
    return sortAndCount(input)
}

console.log(doTheStuff())