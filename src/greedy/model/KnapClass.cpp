//
// Created by Luca Di Bello on 22.03.23.
//

#include "KnapClass.h"

KnapClass::KnapClass(int nitems, int nresources): nitems(nitems), nresources(nresources) {};

int KnapClass::getNitems() const {
    return nitems;
}

int KnapClass::getNresources() const {
    return nresources;
}
