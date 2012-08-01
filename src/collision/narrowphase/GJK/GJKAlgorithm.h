/********************************************************************************
* ReactPhysics3D physics library, http://code.google.com/p/reactphysics3d/      *
* Copyright (c) 2010-2012 Daniel Chappuis                                       *
*********************************************************************************
*                                                                               *
* This software is provided 'as-is', without any express or implied warranty.   *
* In no event will the authors be held liable for any damages arising from the  *
* use of this software.                                                         *
*                                                                               *
* Permission is granted to anyone to use this software for any purpose,         *
* including commercial applications, and to alter it and redistribute it        *
* freely, subject to the following restrictions:                                *
*                                                                               *
* 1. The origin of this software must not be misrepresented; you must not claim *
*    that you wrote the original software. If you use this software in a        *
*    product, an acknowledgment in the product documentation would be           *
*    appreciated but is not required.                                           *
*                                                                               *
* 2. Altered source versions must be plainly marked as such, and must not be    *
*    misrepresented as being the original software.                             *
*                                                                               *
* 3. This notice may not be removed or altered from any source distribution.    *
*                                                                               *
********************************************************************************/

#ifndef GJK_ALGORITHM_H
#define GJK_ALGORITHM_H

// Libraries
#include "../NarrowPhaseAlgorithm.h"
#include "../../ContactInfo.h"
#include "../../../colliders/Collider.h"
#include "../EPA/EPAAlgorithm.h"


// ReactPhysics3D namespace
namespace reactphysics3d {

// Constants
const decimal REL_ERROR = 1.0e-3;
const decimal REL_ERROR_SQUARE = REL_ERROR * REL_ERROR;

/*  -------------------------------------------------------------------
    Class GJKAlgorithm :
        This class implements a narrow-phase collision detection algorithm. This
        algorithm uses the ISA-GJK algorithm and the EPA algorithm. This
        implementation is based on the implementation discussed in the book
        "Collision Detection in 3D Environments".
        This method implements the Hybrid Technique for calculating the
        penetration depth. The two objects are enlarged with a small margin. If
        the object intersection, the penetration depth is quickly computed using
        GJK algorithm on the original objects (without margin). If the
        original objects (without margin) intersect, we run again the GJK
        algorithm on the enlarged objects (with margin) to compute simplex
        polytope that contains the origin and give it to the EPA (Expanding
        Polytope Algorithm) to compute the correct penetration depth between the
        enlarged objects. 
    -------------------------------------------------------------------
*/
class GJKAlgorithm : public NarrowPhaseAlgorithm {
    private :
        EPAAlgorithm algoEPA;             // EPA Algorithm

        bool computePenetrationDepthForEnlargedObjects(const Collider* collider1, const Transform& transform1,
                                                       const Collider* collider2, const Transform& transform2,
                                                       ContactInfo*& contactInfo, Vector3& v);             // Compute the penetration depth for enlarged objects

    public :
        GJKAlgorithm(MemoryPool<ContactInfo>& memoryPoolContactInfos);  // Constructor
        ~GJKAlgorithm();                                                // Destructor

        virtual bool testCollision(const Collider* collider1, const Transform& transform1,
                                   const Collider* collider2,  const Transform& transform2,
                                   ContactInfo*& contactInfo);                      // Return true and compute a contact info if the two bounding volume collide
};

} // End of the ReactPhysics3D namespace

#endif