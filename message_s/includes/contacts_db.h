#include "contact.h"
#include <string>

/*!
    \brief Application namespace

    Namespace "message_s" will be used all over application
 */

namespace message_s
{
        /*!
	 * \brief The contacts database class
	 *
	 * Using to manage contacts database on physical memory. This class will work with contacts DB by adress. Encryption and decryption included.
	 */
        class contact_db
	{
	public:
	        /*!
		 * \brief "contact_db" constructor
		 * \param adress Contacts database adress
		 * \param key Encryption key for DB
		 */
	                            contact_db(std::string adress, std::string key);
		/*!
		 * \brief "contact_db" destructor
		 */
				    ~contact_db();
		/*!
		 * \brief Returns contact by ID
		 * \param id ID of requesting contact
		 * \return Contact class
		 */
		message_s::contact  get_contact(unsigned int id);
		/*!
		 * \brief Adds contact to database and gives it ID
		 * \param cntkt Contact that should be added
		 * \return New ID of contact in DB
		 */
		unsigned int	    add_contact(message_s::contact cntkt);
		/*!
		 * \brief Removes contact from DB by ID
		 * \param id ID of contact shoul be removed
		 * \return True if removal had been succesful, False in case of error
		 */
		bool		    remove_contact(unsigned int id);
		/*!
		 * \brief Saves DB to physical memory
		 * \return True if saving succsesful, False ni case of error
		 */
		bool		    save_base();
		/*!
		 * \brief Reloading base from physical memory
		 * \warning Current version of database will be deleted and replaced by version from physical memory!
		 * \return True if reload succsesful, False in case of error
		 */
		bool		    reload_base();

	private:
		/*!
		 * \brief Array of IDs that less than last used ID, but not used
		 */
		unsigned int	    *free_ids;
		/*!
		 * \brief Amouth of contacts in DB
		 */
		unsigned int	    amouth;
		/*!
		 * \brief Array of contacts sorted by IDs
		 */
		message_s::contact* contacts;
		/*!
		 * \brief current adress of database
		 */
		char*		    adress;
	};
}
