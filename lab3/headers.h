#ifndef H_HEADERS
#define H_HEADERS

#include <string>

class Header{

	public:
	enum class OsiLayer {PHY=1,MAC,NET,TRAN,SESS,PRES,APP};
	Header(OsiLayer,int);
	virtual ~Header();
	virtual std::string getInfo() const = 0;
	void setSize(int);
	int getSize() const;
	OsiLayer getLayer() const;
	
	protected:
	int size;
	const OsiLayer layer;

};
#endif
