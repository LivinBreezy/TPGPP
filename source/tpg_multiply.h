#ifndef TPG_OPERATIONS_TPGMULTIPLY_H_
#define TPG_OPERATIONS_TPGMULTIPLY_H_

#include "tpg_utility.h"

#include <string>

#include <boost/serialization/split_member.hpp>
#include "tpg_operation.h"

class MultiplyOperation : public Operation
{
    friend class boost::serialization::access;

    template<class Archive>
    void save(Archive& ar, const unsigned int version)
    {

    }

    template<class Archive>
    void load(Archive& ar, const unsigned int version)
    {

    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

public:
    bool execute(int8, 
        int32, 
        int8, 
        const std::vector<double>&, 
        std::vector<double>&,
        TpgParameters&) const;
    std::string toString() const;
    std::string toStorage() const;
};

#endif