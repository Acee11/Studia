tree(leaf) --> "*",!.
tree(node(X,Y)) --> "(", tree(X), tree(Y), ")".



tree1 --> "*".
tree1 --> "(", tree1, tree1, ")".