/**********************************************************************
  Bond - A basic bond class. Just stores two atom indices and a bond order.
         There is potential for more to be added in the future...

  Copyright (C) 2017 by Patrick S. Avery

  This source code is released under the New BSD License, (the "License").

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 ***********************************************************************/

#ifndef GLOBALSEARCH_BOND_H
#define GLOBALSEARCH_BOND_H

namespace GlobalSearch
{

 /**
  * @class Bond bond.h
  * @brief A basic bond class. Just stores two atom indices and a bond order.
  *        There is potential for more to be added in the future...
  */
  class Bond
  {
   public:
    /**
     * Bond constructor. Default bond order is 1.
     *
     * @param ind1 The index of the first atom in the bond.
     * @param ind2 The index of the second atom in the bond.
     * @param bondOrder The bond order. Default is 1.
     */
    explicit Bond(size_t ind1, size_t ind2, unsigned short bondOrder = 1);

    /* Default destructor */
    ~Bond() = default;

    /* Default copy constructor */
    Bond(const Bond& other) = default;

    /* Default move constructor */
    Bond(Bond&& other) = default;

    /* Default assignment operator */
    Bond& operator=(const Bond& other) = default;

    /* Default move assignment operator */
    Bond& operator=(Bond&& other) = default;

    /**
     * Get the index of the first atom in the bond.
     *
     * @return The index of the first atom in the bond.
     */
    size_t first() const { return m_ind1; }

    /**
     * Get the index of the second atom in the bond.
     *
     * @return The index of the second atom in the bond.
     */
    size_t second() const { return m_ind2; }

    /**
     * Set the bond order. Should be 1, 2, 3, or 4...
     *
     * @param o The bond order.
     */
    void setBondOrder(unsigned short o) { m_bondOrder = o; }

    /**
     * Get the bond order.
     *
     * @return The bond order.
     */
    unsigned short bondOrder() const { return m_bondOrder; }

   private:
    size_t m_ind1, m_ind2;
    unsigned short m_bondOrder;
  };

  // Make sure the move constructor is noexcept
  static_assert(std::is_nothrow_move_constructible<Bond>::value,
                "Bond should be noexcept move contructible.");

  // Make sure the move assignment operator is noexcept
  static_assert(std::is_nothrow_move_assignable<Bond>::value,
                "Bond should be noexcept move assignable.");

  inline Bond::Bond(size_t ind1, size_t ind2, unsigned short bondOrder)
    : m_ind1(ind1),
      m_ind2(ind2),
      m_bondOrder(bondOrder)
  {
  }
}

#endif
