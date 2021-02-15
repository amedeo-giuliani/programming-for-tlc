/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

/**
 * @file modem.h
 * @author Filippo Campagnaro
 * @version 1.0.0
 * @brief Class describing a modem that can be configured.
 */

#ifndef H_MODEM
#define H_MODEM

#include <ethernet-connector.h>
/**
 * class Modem containing the parameters to be configured
 */
class Modem
{
public:
    
  /**
   * Class constructor.
   * @param tx_pwr transmission power, in milliwatt
   * @param rate bitrate, in bps
   * @param verb flag set to true if verbose output is required
   */
  Modem(unsigned int tx_pwr = 100, unsigned int rate = 1000, bool verb = true);

  /**
   * Class destructor.
   */
  virtual ~Modem() {}


  /**
   * perform the configuration
   * @param buffer pointing to the C string 
   * @param input_size of the string to parse
   * @param output_size output parameter with size of the output string to 
   *        store in the buffer
   * @param is_exit output parameter set to true if the configure command is 
   *        equal to "EXIT"
   * @return true if configuration succeeded
   */
  bool configure(std::shared_ptr<std::array<char, MTU>> buffer, 
    size_t input_size, size_t& output_size, bool& is_exit);


  // EXERCISE 3: Declare and implement the methods getTxPower(), getBitrate(),  
  // getVerbose() and getConfigurationsCounter() that return transmission power,
  // bitrate, if the output is verbose, and the number of successful 
  // configurations, respectively, without modifying any parameter of the class.
  

  /**
   * get the transmission power, in milliwatt
   * @return the transmission power, in milliwatt
   */
  /*Add your code here*/
  unsigned int getTxPower() const;

  /**
   * get the bitrate, in bps
   * @return the bitrate, in bps
   */
  /*Add your code here*/
  unsigned int getBitrate() const;

  /**
   * get if the output is verbose or not
   * @return true if verbose output is required
   */
  /*Add your code here*/
  bool getVerbose() const;

  /**
   * get the number of successful configurations
   * @return the number of successful configurations
   */
  /*Add your code here*/
  unsigned int getConfigurationsCounter() const;

private:

  /**
   * parse and configure the parameter
   * @param configuration string with the configuration to be parsed 
   * @param is_exit output parameter set to true if the configure command was "EXIT"
   * @return true if configuration succeeded
   */
  bool parse(const std::string& configuration, bool& is_exit);


  /** constant string used for setting the transmission power from socket*/
  static const std::string SET_TX_POWER;
  /** constant string used for setting the bitrate command from socket*/
  static const std::string SET_BITRATE;
  /** constant string used whether to enable the verbose output from socket*/
  static const std::string SET_VERBOSE;
  /** constant string used to quit the program from socket*/
  static const std::string QUIT;  
  /** constant string used answer the user that it provided a wrong configuration*/
  static const std::string ERROR;
  /** constant string used answer the user that it provided a valid configuration*/
  static const std::string SUCCESS;

  unsigned int tx_power; /**<transmission power, in milliwatt*/
  unsigned int bitrate; /**<bitrate, in bps*/
  bool verbose; /**<flag set to true if verbose output is required*/
  unsigned int config_counter; /**<number of successful configurations*/

};


#endif /* H_MODEM */
