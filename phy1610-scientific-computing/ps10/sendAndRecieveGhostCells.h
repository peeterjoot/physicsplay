/** \file sendAndRecieveGhostCells.h
 */
#if !defined phy1610_sendAndRecieveGhostCells_h_included
#define phy1610_sendAndRecieveGhostCells_h_included

/**
   Send right ghost cell right.
   Send left ghost cell left.
   Recieve right's left ghost cell.
   Recieve lefts's right ghost cell.

   Illustrating by example.  We want to make the transformation from an initial global domain:

   rank:   0         1         2
      | 0 ... 1 | 2 ... 3 | 4 ... 5 |

   To the following global domain:

   rank:   0         1         2
      | 0 ... 2 | 1 ... 4 | 3 ... 5 |

   \param myLeftGhostCell [in]
      In the example above, R1 sends 2 to R0 from this parameter.

   \param myRightGhostCell [in]
      In the example above, R1 sends 3 to R2 from this parameter.

   \param pLeftGhostCellFromRight [out]
      In the example above, R1 receives 4 from R2 into this address.

   \param pRightGhostCellFromLeft [out]
      In the example above, R1 receives 1 from R0 into this address.

   \param size [in]
      Communicator size.

   \param rank [in]
      Rank of active task.

   \retval
      Throws exception on error.
 */
void sendAndRecieveGhostCells( const float   myLeftGhostCell,
                               const float   myRightGhostCell,
                               float *       pLeftGhostCellFromRight,
                               float *       pRightGhostCellFromLeft,
                               const int     size,
                               const int     rank ) ;
#endif
