

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
        self.root = 0
        #print("Node root created.")

    
    def insert(self):
        city = str(input("Digit the name of city: "))
        posx = int(input("Digit the coordinate x: "))
        posy = int(input("Digit the coordinate y: "))
        
        if (self.root==0):
            self.root = Link(city, posx, posy)
            print("Root created.")
        else:
            #print("In recursion...")
            self.insertAux(self.root, city, posx, posy)


    def insertAux(self, root, city, posx, posy):
        #print("root aqui:", root.name_city)
        if (root.getLeft()==0):
            new_node = Link(city, posx, posy)
            root.setLeftNode(new_node)
            return
        elif (root.getRight()!=0):
            self.insertAux(root.getLeft(), city, posx, posy)
        
        if (root.getRight()==0):
            new_node = Link(city, posx, posy)
            root.setRightNode(new_node)
            return
        else:
            self.insertAux(root.getRight(), city, posx, posy)


    def getRoot(self):
        return self.root


    def ShowAllInOrder(self, root):
        #print("-{}-".format(root.name_city))
        if (root.getLeft()!=0):
            self.ShowAllInOrder(root.getLeft())
        print("-{}-".format(root.name_city))
        if (root.getRight()!=0):
            self.ShowAllInOrder(root.getRight())
            #print("-{}-".format(root.name_city))
        return

    
    def searchByName(self, root, name_city):
        #print("init: -", root.name_city, name_city)
        sroot = None
        if (root.name_city == name_city): return root
        if (root.getLeft()!=0):
            sroot = self.searchByName(root.getLeft(), name_city)
        if (root.getRight()!=0):
            sroot = self.searchByName(root.getRight(), name_city)
        return sroot 



    def searchByCoord(self, root, x, y):
        sroot = None
        if (root.positions[0]==x) and (root.positions[1]==y): return root
        if (root.getLeft()!=0):
            sroot = self.searchByCoord(root.getLeft(), x, y)
        if (root.getRight()!=0):
            sroot = self.searchByCoord(root.getRight(), x, y)
        return sroot 



def ShowMenu():
    title = str("TREE OF CITIES")
    lenght = len(title)
    for i in range(lenght): print("#", end="")
    print("\n", end="")
    print(title)
    for i in range(lenght): print("#", end="")
    print("\n", end="")
    print("1 - Insert city.")
    print("2 - Remove city by name.")
    print("3 - Remove city by coordinate.")
    print("4 - Search city by name.")
    print("5 - Search city by coordinate.")
    print("6 - Search by distance although of one point (x,y).")
    print("7 - Show all in order")
    print("8 - Exit the program.")

    
def main():
    tree = nodeTree()

    opt = int(0)
    while(opt!=8):
        ShowMenu()
        opt = int(input("Digit one option: "))
        if (opt==1):
            tree.insert()
        elif (opt==4):
            name = str(input("Digit the name of city to search: "))
            search = tree.searchByName(tree.getRoot(), name)
            if (search!=None):
                print("City {} finded in ({},{})".format(search.name_city, search.positions[0],
                 search.positions[1]))
            else: print("City not finded.")
        elif (opt==5):
            x = int(input("Digit the coordinate x: "))
            y = int(input("Digit the coordinate y: "))
            search = tree.searchByCoord(tree.getRoot(), x, y)
            if (search!=None):
                print("City {} finded in ({},{})".format(search.name_city, search.positions[0],
                 search.positions[1]))
            else: print("City not finded.")
        elif (opt==7):
            tree.ShowAllInOrder(tree.getRoot())


main()