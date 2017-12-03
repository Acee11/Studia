var Tree = function (value, left, right) {
    if(left === undefined) {
        left = null
    }
    if(right === undefined) {
        right = null
    }
    this.value = value
    this.left = left
    this.right = right
}
Tree.prototype.print = function () {
    let left = this.left === null ? '' : this.left.print()
    let right = this.right === null ? '' : this.right.print()
    return `${left} ${this.value} ${right}`
}

let leftSubtree = new Tree(2, new Tree(3), new Tree(4))
let rightSubtree = new Tree(
    5, 
    new Tree(6, new Tree(8)), 
    new Tree(7)
)
let root = new Tree(1, leftSubtree, rightSubtree)


console.log(root.print())