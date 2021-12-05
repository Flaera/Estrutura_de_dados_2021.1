

class Link():
    def __init__(self, city=str(""), posx=int(0), posy=int(0)):
        self.name_city = str(city)
        self.positions = [0.0, 0.0]
        self.positions[0] = int(posx)
        self.positions[1] = int(posy)
        self.left = 0
        self.right = 0


    def getNameCity(self):return self.name_city
    def getPosX(self):return self.positions[0]
    def getPosY(self):return self.positions[1]
    def getLeft(self):return self.left
    def getRight(self):return self.right
    def setLeftNode(self, node):self.left = node
    def setRightNode(self, node):self.right = node


class nodeTree():
    def __init__(self):
        self.root = Link()
        print("Node root created.")

    
    def insert(self):
        city = str(input("Digit the name of city: "))
        posx = int(input("Digit the coordinate x: "))
        posy = int(input("Digit the coordinate y: "))
        print("root aqui:", self.root)
        if (self.root.getLeft() == 0):
            self.root = Link(city, posx, posy)
        elif (self.root.getRight() == 0):
            self.root = Link(city, posx, posy)
        else:
            self.insertAux(self.root, city, posx, posy)


    def insertAux(self, root, city, posx, posy):
        if (root.getLeft()!=0):
            new_node = Link(city, posx, posy)
            root.setLeftNode(new_node)
        else:
            self.insertAux(root.getLeft(), city, posx, posy)
        
        if (root.getRight()!=0):
            new_node = Link(city, posx, posy)
            root.setRightNode(new_node)
        else:
            self.insertAux(root.getRight(), city, posx, posy)


    def getRoot(self):
        return self.root


    def ShowAllInOrder(self, root):
        if (root.getLeft()!=0):
            self.ShowAllInOrder(root.getLeft())
            print("-{}-".format(root.name_city))
        if (root.getRight()!=0):
            self.ShowAllInOrder(root.getRight())
        return

    
def main():
    tree = nodeTree()

    opt = int(0)
    while(opt!=8):
        opt = int(input("Digit one option: "))
        if (opt==1):
            tree.insert()
        elif (opt==7):
            tree.ShowAllInOrder(tree.getRoot())


main()