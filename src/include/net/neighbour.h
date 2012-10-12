/**
 * @file
 * @brief Implementation of ARP Cache
 *
 * @date 12.08.11
 * @author Ilia Vaprol
 */

#ifndef NET_NEIGHBOUR_H_
#define NET_NEIGHBOUR_H_

#include <net/netdevice.h>

/**
 * Neighbour entity
 */
struct neighbour {
	unsigned char haddr[MAX_ADDR_LEN]; /* Hardware address */
	unsigned char hlen;                /* Length of hw address */
	unsigned char paddr[MAX_ADDR_LEN]; /* Protocol address */
	unsigned char plen;                /* Length of protocol address */
	const struct net_device *dev;      /* Network device */
	unsigned char flags;               /* Additional information */
};

/**
 * Neighbour flags
 */
#define NEIGHBOUR_FLAG_PERMANENT 0x01 /* Permanent entity */

/**
 * This function add entry in neighbour (rewrite non-permanent entity)
 * @param haddr - hardware address (not null)
 * @param hlen  - length of haddr (not zero)
 * @param paddr - protocol address (not null)
 * @param plen  - length of paddr (not zero)
 * @param dev   - network device (not null)
 * @param flags - flags for this entity
 * @return error code
 */
extern int neighbour_add(const unsigned char *haddr, unsigned char hlen,
		const unsigned char *paddr, unsigned char plen,
		const struct net_device *dev, unsigned char flags);

/**
 * This function delete entry from neighbour if can
 * @param haddr - hardware address (not null if hlen not zero and null
 *                otherwise; can't be null if paddr null)
 * @param hlen  - length of haddr (as haddr)
 * @param paddr - protocol address (not null if plen not zero and null
 *                otherwise; can't be null of haddr null)
 * @param plen  - length of paddr (as haddr)
 * @param dev   - network device
 * @return error code
 */
extern int neighbour_del(const unsigned char *haddr, unsigned char hlen,
		const unsigned char *paddr, unsigned char plen,
		const struct net_device *dev);

/**
 * This function search entry by protocol address
 * @param paddr     - protocol address (not null)
 * @param plen      - length of paddr (not zero)
 * @param dev       - network device
 * @param hlen_max  - max size of hardware address (not zero)
 * @param out_haddr - pointer to the location to write the hardware
 *                    address (not null)
 * @param out_hlen  - pointer to the location to write length of the
 *                    out_haddr (if null and the real out_hlen not equal
 *                    to hlen_max then error will returned)
 * @return error code
 */
extern int neighbour_get_hardware_address(const unsigned char *paddr,
		unsigned char plen, const struct net_device *dev, unsigned char hlen_max,
		unsigned char *out_haddr, unsigned char *out_hlen);

/**
 * This function search entry by hardware address
 * @param haddr     - hardware address (not null)
 * @param hlen      - length of haddr (not zero)
 * @param dev       - network device
 * @param plen_max  - max size of protocol address (not zero)
 * @param out_paddr - pointer to the location to write the protocol
 *                    address (not null)
 * @param out_plen  - pointer to the location to write length of the
 *                    out_paddr (if null and the real out_plen not equal
 *                    to plen_max then error will returned)
 * @return error code
 */
extern int neighbour_get_protocol_address(const unsigned char *haddr,
		unsigned char hlen, const struct net_device *dev, unsigned char plen_max,
		unsigned char *out_paddr, unsigned char *out_plen);

/**
 * Type of handler for neighbour_foreach function
 */
typedef int (*neighbour_foreach_handler_t)(const struct neighbour *n, void *args);

/**
 * This function processes each entry in the table with func handler.
 * If during the processing of the entity handler returns an error,
 * the process is interrupted.
 * @param func - handler for each entity (not null)
 * @param args - additional arguments for func
 * @return error code
 */
extern int neighbour_foreach(neighbour_foreach_handler_t func, void *args);

#endif /* NET_NEIGHBOUR_H_ */
