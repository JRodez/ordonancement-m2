from threading import Thread
from time import sleep
from enum import Enum

# Etape 1, sans gestion des défaillances
# Seul le superviseur est implémenté pour visualisation du fonctionnement des threads par pièce, comme indiqué dans le sujet.
# ainsi seul ce qui concerne le superviseur est afficher.




class TypeUsinage(Enum):
    A = 0
    B = 1
    C = 2



class Th_Machine():
    def prendre():
        return "priseConf"

    def usinageReq(type_piece):
        sleep(1)
        return "usinageConf"

    def depotFini():
        sleep(3)
        return "finUsinage"

    def remiseReq():
        sleep(1)
        return "remiseConf"


class Th_Robot_Alim():
    def depotReq():
        sleep(1)
        return "depotConf"


class Th_Robot_Ret():
    def retraitReq():
        sleep(1)
        return "retraitConf"



class Th_Piece():
    def __init__(self):
        self.thread_pieces = {}  # Dictionnaire des threads en cours à qui est associé leur état

    def pieceArv(self, type_piece):
        """
        Cree un thread pour traiter la piece.
        """
        id = len(self.thread_pieces)
        thread = None

        def traitementPiece():
            print(f"ID={id} | Envoie de usinageReq à Th_Machine")
            msg = Th_Machine.usinageReq(type_piece)
            print(f"ID={id} | Réception de {msg} de Th_Machine")

            print(f"ID={id} | Envoie de depotReq à Th_Robot_Alim")
            msg = Th_Robot_Alim.depotReq()
            print(f"ID={id} | Réception de {msg} de Th_Robot_Alim")

            print(f"ID={id} | Envoie de depotFini à Th_Machine")
            print(f"ID={id} | Usinage...")
            msg = Th_Machine.depotFini()  # Usinage...
            print(f"ID={id} | Réception de {msg} de Th_Machine")

            print(f"ID={id} | Envoie de remiseReq à Th_Machine")
            msg = Th_Machine.remiseReq()
            print(f"ID={id} | Réception de {msg} de Th_Machine")

            print(f"ID={id} | Envoie de retraitReq à Th_Robot_Ret")
            msg = Th_Robot_Ret.retraitReq()
            print(f"ID={id} | Réception de {msg} de Th_Robot_Ret")
            print(f"ID={id} | Piece traitée")
            return
        
        thread = Thread(target=traitementPiece)
        self.thread_pieces[thread] = id
        thread.start()



SUPERVISEUR = Th_Piece()  # Th_Piece dans SDL

if __name__ == '__main__':

    # operateur :
    SUPERVISEUR.pieceArv(TypeUsinage.A)
    sleep(1)
    SUPERVISEUR.pieceArv(TypeUsinage.B)
    sleep(1)
    SUPERVISEUR.pieceArv(TypeUsinage.C)
    sleep(1)
