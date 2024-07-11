/**CFile****************************************************************

  FileName    [mapper.c]

  PackageName [MVSIS 1.3: Multi-valued logic synthesis system.]

  Synopsis    [Command file for the mapper package.]

  Author      [MVSIS Group]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 2.0. Started - June 1, 2004.]

  Revision    [$Id: mapper.c,v 1.7 2005/01/23 06:59:42 alanmi Exp $]

***********************************************************************/

#ifndef ABC__src__map__mapper__CoolMapper__c
#define ABC__src__map__mapper__CoolMapper__c

#include "base/abc/abc.h"
#include "map/mio/mio.h"
#include "map/mapper/mapper.h"

ABC_NAMESPACE_IMPL_START

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

Abc_Obj_t ** Abc_NtkGetPisArray(Abc_Ntk_t * pNtk) {
    Abc_Obj_t * pObj;
    Abc_Obj_t ** ppPis;
    int i;

    ppPis = ABC_ALLOC(Abc_Obj_t *, Abc_NtkPiNum(pNtk));
    Abc_NtkForEachPi(pNtk, pObj, i) {
        ppPis[i] = pObj;
    }
    return ppPis;
}

/**Function*************************************************************

  Synopsis    []

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
Abc_Ntk_t * Abc_NtkCreateFromSuperGate2(Map_Super_t *pSuper, Mio_Library_t *pLib) {
    Abc_Ntk_t * pNtkNew;
    Abc_Obj_t * pNodeNew, * pNodeFanin;
    Map_Super_t ** ppFanins;
    Mio_Gate_t * pRoot;
    int nFanins, i;

    // assert(pSuper != NULL);
    // assert(pLib != NULL);
    if(!pSuper){
        printf("psuper is null");
        return NULL;
    }
    if(!pLib){
        printf("plib is null");
        return NULL;
    }

    // Create a new empty network
    pNtkNew = Abc_NtkAlloc(ABC_NTK_LOGIC, ABC_FUNC_SOP, 1); 

    // Get the parameters of the supergate
    pRoot = Map_SuperReadRoot(pSuper);
    nFanins = Map_SuperReadFaninNum(pSuper);
    ppFanins = Map_SuperReadFanins(pSuper);

    // Create PI nodes for each fanin of the supergate
    for (i = 0; i < nFanins; i++) {
        pNodeFanin = Abc_NtkCreatePi(pNtkNew);
    }

    Abc_Obj_t *  Abc_NodeFromMapSuperChoice_rec( Abc_Ntk_t * pNtkNew, Map_Super_t * pSuper, Abc_Obj_t * pNodePis[], int nNodePis );
    // Recursively build the internal logic of the supergate
    pNodeNew = Abc_NodeFromMapSuperChoice_rec(pNtkNew, pSuper, Abc_NtkGetPisArray(pNtkNew), nFanins);

    // Create a primary output and connect the supergate output to it
    Abc_ObjAddFanin(Abc_NtkCreatePo(pNtkNew), pNodeNew);

    // Set the name of the network (optional)
    Abc_NtkSetName(pNtkNew, Mio_GateReadName(pRoot));

    return pNtkNew;
}


////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////


ABC_NAMESPACE_IMPL_END



#endif