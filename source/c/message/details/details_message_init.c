#include <messaging/message/details/message_init.h>

__synapse_messaging_message*
	__synapse_messaging_message_initialize
		(synapse_memory_manager* pMman,
		 uint16_t				 pMsgOpcode, 
		 void*					 pMsgField, 
		 size_t					 pMsgFieldSize)
{
	synapse_memory_block
		hnd_mblock
			= pMman->allocate
				(pMman->hnd_mman, NULL, sizeof(__synapse_messaging_message));
	
	__synapse_messaging_message*
		ptr_message
			= pMman->block_pointer
				(hnd_mblock);

	ptr_message->msg_field_ptr
		= pMsgField;
	ptr_message->msg_field_size
		= pMsgFieldSize;
	
	ptr_message->msg_mman_block
		= hnd_mblock;
	ptr_message->msg_opcode
		= pMsgOpcode;

	return
		ptr_message;
}

void
	__synapse_messaging_message_cleanup
		(synapse_memory_manager* pMman, __synapse_messaging_message* pMessage)
{
	pMman->deallocate
		(pMman->hnd_mman, pMessage->msg_mman_block);
}