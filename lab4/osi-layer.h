/*
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/
#ifndef H_OSI_L
#define H_OSI_L
#include <iostream>
#include <string>
#include <memory>
#include <queue>

/**
 * Struct Packet that does nothing just for example
 */
struct Packet
{
  //THERE SHOULD BE SOMETHING HERE.. JUST AS EXAMPLE
  int u_id; /**<unique id*/
  char buf[200] = {};
  size_t offset;
  /**
   * Struct constructor
   * @param id unique id
   */
  Packet(int id, size_t o) : u_id(id), offset(o) {}

  /**
   * Struct destructor
   */
  ~Packet(){ std::cout <<"Destructor of Packet pkt" << u_id << std::endl; }
};

/**
 * Class OsiLayer to mock an ISO OSI layer
 */
class OsiLayer {
public:
  /**
   * Class constructor
   * @param name label of the layer
   */
  OsiLayer(const std::string& name);

  /**
   * Class destructor
   */
  virtual ~OsiLayer();

  /**
   * set the lower layer
   * @param l_l pointer to the lower layer
   */
  void setLowerLayer(std::shared_ptr<OsiLayer> l_l);

  /**
   * Set the upper layer
   * @param u_l pointer to the upper layer
   */
  void setUpperLayer(std::shared_ptr<OsiLayer> u_l);

  /**
   * Print the OsivLayer to the ostream
   * @param out a ostream
   */
  void print(std::ostream& out) const;

  /**
   * Send a packet to the upper layer
   * @param p pointer to the packet to be sent
   */
  virtual void sendToUpperLayer(std::shared_ptr<Packet> p);
  /**
   * Send a packet to the lower layer
   * @param p pointer to the packet to be sent
   */
  virtual void sendToLowerLayer(std::shared_ptr<Packet> p);
  /**
   * Push a packet to the output queue
   * @param p pointer to the packet to be pushed
   */
  void addToOutQueue(std::shared_ptr<Packet> p);
  /**
   * Push a packet to the input queue
   * @param p pointer to the packet to be pushed
   */
  void addToInQueue(std::shared_ptr<Packet> p);
protected:
  std::string layer_name; /**< name of the layer*/
  std::weak_ptr<OsiLayer> upper_layer;/**<pointer to the upper layer*/
  std::weak_ptr<OsiLayer> lower_layer;/**<pointer to the lower layer*/
  std::queue<std::shared_ptr<Packet>> out_q; /**< queue with the packet to send*/
  std::queue<std::shared_ptr<Packet>> in_q; /**< queue with the packet to rx*/
};

/**
 * Overloaded operator<< for a osi layer
 * @param out a std::ostream object
 * @param layer a layer to be printed
 * @return the manipulated ostream object
 */
std::ostream& operator<<(std::ostream& out, const OsiLayer& layer);

#endif //H_OSI_L
