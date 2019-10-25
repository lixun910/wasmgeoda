#ifndef __JSGEODA_GWT_WEIGHT_H__
#define __JSGEODA_GWT_WEIGHT_H__

#include <vector>
#include "GeodaWeight.h"
#include "GalWeight.h"

struct GwtNeighbor {
	long nbx;
	double weight;
	GwtNeighbor(const long nb=0, const double w=0) : nbx(nb), weight(w) {}
	void assign(const long nb=0, const double w=0) { nbx=nb;  weight=w; }
};

class GwtElement {
public:
	long nbrs; // current number of neighbors
	GwtNeighbor* data; // list neighborhood
	
public:
	GwtElement() : data(0), nbrs(0) {}
	virtual ~GwtElement();
    
	bool alloc(const int sz);
    
	bool empty() const { return data == 0; }
    
	void Push(const GwtNeighbor &elt) { data[nbrs++] = elt; }
    
	GwtNeighbor Pop() { return !nbrs ? GwtNeighbor(-1) : data[--nbrs]; }
    
	long Size() const { return nbrs; }
    
	GwtNeighbor elt(const long where) const { return data[where]; }
    
	GwtNeighbor* dt() const { return data; }
    
	double SpatialLag(const std::vector<double>& x, const bool std=true) const;
    
	double SpatialLag(const double* x, const bool std=true) const;

    bool Check(long nbr_idx);

    std::vector<long> GetNbrs();
};


class GwtWeight : public GeoDaWeight {
public:
	GwtWeight() : gwt(0) { weight_type = gwt_type; }
	virtual ~GwtWeight() { if (gwt) delete [] gwt; gwt = 0; }
	GwtElement* gwt;
	static bool HasIsolates(GwtElement *gwt, int num_obs);
    
	virtual bool HasIsolates() { return HasIsolates(gwt, num_obs); }
    virtual bool CheckNeighbor(int obs_idx, int nbr_idx);
    virtual const std::vector<long> GetNeighbors(int obs_idx);
    virtual void Update(const std::vector<bool>& undefs);
    virtual void GetNbrStats();
    virtual int GetNbrSize(int obs_idx);
    virtual double SpatialLag(int obs_idx,
                              const std::vector<double>& data);
};

namespace Gda {
    GalElement* Gwt2Gal(const GwtElement* g, int num_obs);
}

#endif