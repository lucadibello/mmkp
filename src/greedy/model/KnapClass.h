//
// Created by Luca Di Bello on 22.03.23.
//

#ifndef MMKP_KNAPCLASS_H
#define MMKP_KNAPCLASS_H


class KnapClass {
public:
    KnapClass(int nitems, int nresources);
    int getNitems() const;
    int getNresources() const;
private:
    int nitems;
    int nresources;
};


#endif //MMKP_KNAPCLASS_H
