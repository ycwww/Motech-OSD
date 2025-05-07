#ifndef SLSIMAXDATA_H_
#define SLSIMAXDATA_H_

//#include "slsimconfig.h"
#include "slsimglbconst.h"

template<typename T, typename AxisIterator>
class AxesValuesIterator;

template<typename T>
class AxesBitfieldIterator
{
public:
  typedef typename T::idx_type idx_type;
  typedef typename T::idx_type value_type;

  AxesBitfieldIterator(T bitfield) : m_bitfield(bitfield), m_position(-1) {
    operator++();
  }
  
  AxesBitfieldIterator() : m_position(-1) {
      memset(&m_bitfield, 0, sizeof(T));
  }
  
  bool operator!=(AxesBitfieldIterator rhs) const {
    return m_position != rhs.m_position;
  }

  bool operator==(AxesBitfieldIterator rhs) const {
    return m_position == rhs.m_position;
  }

  idx_type operator*() const {
    idx_type result = { static_cast<typename idx_type::base_type>(m_position + idx_type::used_tag::min_idx) };
    return result;
  }
 
  inline void operator++() {
    ++m_position;
    while(m_position <= (char)sizeof(unsigned int)*8 && (m_position + idx_type::used_tag::min_idx) <= idx_type::used_tag::max_idx)
    {
      if( SL_HMI_CHECK_BITNUM(m_bitfield.value, m_position) )
        return;
      ++m_position;
    }
    m_position = -1;
  }
 
private:
  T m_bitfield;
  char m_position;
};

template<typename T, typename IndexType, int N>
struct AxesValues
{
    typedef T value_type;
    typedef IndexType index_type;
    typedef axes_bitfield<index_type> native_bitfield;

    inline value_type& operator[](index_type idx) {
       Q_ASSERT(idx.valid());
       Q_ASSERT(indexToOffset(idx) < N);
       return data[indexToOffset(idx)];
    }

    inline const value_type& operator[](index_type idx) const {
       Q_ASSERT(idx.valid());
       Q_ASSERT(indexToOffset(idx) < N);
       return data[indexToOffset(idx)];
    }

    typedef AxesValuesIterator<AxesValues, AxesBitfieldIterator<native_bitfield> > bitfield_iterator;
  
    bitfield_iterator begin(axes_bitfield<index_type> bfield) {
       AxesBitfieldIterator<native_bitfield> it = AxesBitfieldIterator<native_bitfield>(bfield);
       return bitfield_iterator(*this, it);
    }

    bitfield_iterator end(axes_bitfield<index_type>) {
       return bitfield_iterator();
    }

    typedef AxesValuesIterator<AxesValues, CompleteIndexIterator<index_type> > iterator;
    
    iterator begin() {
      CompleteIndexIterator<index_type> beg(index_type::create_min());
      return iterator(*this, beg);
    }

    iterator end() {
      return iterator();
    }

    inline int indexToOffset(index_type idx) const {
       return idx.value - IndexType::used_tag::min_idx;
    }

    bool operator==(const AxesValues& other) const {
        return std::equal (data, data + N, other.data);
    }
    bool operator!=(const AxesValues& other) const {
        return !operator==(other);
    }

    value_type data[N];
};

typedef AxesValues<double, chanax_idx, SL_SIM_CHAX_MAXNUM> ChanaxPosData;
typedef AxesValues<double, machax_idx, SL_SIM_AXIS_MAXNUM> MachaxPosData;
typedef AxesValues<short, chanax_idx, SL_SIM_CHAX_MAXNUM> ChanaxParData;
typedef AxesValues<short, machax_idx, SL_SIM_AXIS_MAXNUM> MachaxParData;

template<typename T_SRC, typename T_DST>
struct copy_constness
{
  typedef T_DST type;
};
template<typename T_SRC, typename T_DST>
struct copy_constness<const T_SRC, T_DST>
{
  typedef const typename copy_constness<T_SRC, T_DST>::type type;
};

template<typename T>
class AxesValuesFacade
{
public:
  //typedef typename DataType value_type;
  typedef typename copy_constness<T, typename T::value_type>::type value_type;
  typedef typename T::index_type native_index;
  typedef typename T::native_bitfield native_bitfield;

  AxesValuesFacade(const SlSimConfig *config, int channel, T& data) : m_config(config), m_data(data), m_channel(channel) {
  }

  const T& data() const {
    return m_data;
  }

  T& data() {
    return m_data;
  }

  template<typename IndexType>
  const value_type& operator[](IndexType idx) const {
     return m_data[convertIndex(idx)];
  }

  template<typename IndexType>
  value_type& operator[](IndexType idx) {
     return m_data[convertIndex(idx)];
  }

  template<typename IndexType>
  const value_type& read(IndexType idx, const value_type& def) const {
     native_index nidx = convertIndex(idx);
     if(nidx.valid())
       return m_data[nidx];
     else
       return def;
  }

  template<typename AxisIterator>                              
  AxesValuesIterator<AxesValuesFacade, AxisIterator> begin(AxisIterator it) {
    return AxesValuesIterator<AxesValuesFacade, AxisIterator>(*this, it);
  }

  template<typename AxisIterator>
  AxesValuesIterator<AxesValuesFacade, AxisIterator> end(AxisIterator) {
    return AxesValuesIterator<AxesValuesFacade, AxisIterator>();
  }

  typedef AxesValuesIterator<AxesValuesFacade, AxesBitfieldIterator<native_bitfield> > bitfield_iterator;
  
  bitfield_iterator begin(axes_bitfield<native_index> bfield) {
     AxesBitfieldIterator<native_bitfield> it = AxesBitfieldIterator<native_bitfield>(bfield);
     return bitfield_iterator(*this, it);
  }

  bitfield_iterator end(axes_bitfield<native_index>) {
     return bitfield_iterator();
  }

  //Flags: Koordiantensystem?, Inch? Vielleicht in einer ableitenden Klasse?

private:
  template<typename IndexType>
  inline native_index convertIndex(IndexType idx) const {
     return m_config->convertChannelIndex<native_index>(m_channel, idx);
     //wie ungültige Indices behandeln? Assert? Exception?
  }

  const SlSimConfig *m_config;
  T& m_data;
  int m_channel;
};

typedef AxesValuesFacade<ChanaxPosData> ChanaxPosDataFacade;
typedef AxesValuesFacade<MachaxPosData> MachaxPosDataFacade;
typedef AxesValuesFacade<ChanaxParData>  ChanaxParDataFacade;
typedef AxesValuesFacade<MachaxParData>  MachaxParDataFacade;

typedef AxesValuesFacade<const ChanaxPosData> ChanaxPosDataFacadeConst;
typedef AxesValuesFacade<const MachaxPosData> MachaxPosDataFacadeConst;
typedef AxesValuesFacade<const ChanaxParData>  ChanaxParDataFacadeConst;
typedef AxesValuesFacade<const MachaxParData>  MachaxParDataFacadeConst;


template<typename T, typename AxisIterator>
class AxesValuesIterator
{
public:
  typedef typename T::value_type value_type;
  typedef typename AxisIterator::value_type index_type;

  AxesValuesIterator(T& data, AxisIterator it) : m_data(&data), m_it(it) {
  }

  AxesValuesIterator() : m_data(0), m_it() {}

  inline value_type& operator*() {
    return m_data->operator[](axis_index());
  }

  inline const value_type& operator*() const {
    return m_data->operator[](axis_index());
  }

  inline void operator++() {
    ++m_it;
  }

  inline index_type axis_index() const {
    return *m_it;
  }

  inline bool operator==(const AxesValuesIterator& rhs) {
    return m_it == rhs.m_it;
  }

  inline bool operator!=(const AxesValuesIterator& rhs) {
    return m_it != rhs.m_it;
  }

private:
  T* m_data;
  AxisIterator m_it;
};



#endif
