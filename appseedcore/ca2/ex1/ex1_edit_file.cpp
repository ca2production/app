#include "StdAfx.h"

namespace ex1
{

   edit_file::Item::Item()
   {
   }

   UINT edit_file::Item::read_ch(edit_file * pfile) { return 0; }

   DWORD edit_file::Item::get_position(bool bForward) {UNREFERENCED_PARAMETER(bForward); return m_dwPosition;};
   
   BYTE * edit_file::Item::get_data() { return NULL; }
   edit_file::EItemType edit_file::Item::get_type() { return ItemTypeUndefined; }
   DWORD_PTR edit_file::Item::get_extent() { return 0; }
   DWORD_PTR edit_file::Item::get_file_extent() { return 0; }
   BYTE * edit_file::Item::reverse_get_data() { return NULL; }
   edit_file::EItemType edit_file::Item::reverse_get_type() { return ItemTypeUndefined; }
   DWORD_PTR edit_file::Item::reverse_get_extent() { return 0; }
   DWORD_PTR edit_file::Item::reverse_get_file_extent() { return 0; }
   DWORD_PTR edit_file::Item::get_extent(bool bForward) { return bForward ? get_extent() : reverse_get_extent(); }
   edit_file::EItemType edit_file::Item::get_type(bool bForward) { return bForward ? get_type() : reverse_get_type(); }
   DWORD_PTR edit_file::Item::get_file_extent(bool bForward) { return bForward ? get_file_extent() : reverse_get_file_extent(); }
   BYTE * edit_file::Item::get_data(bool bForward) { return bForward ? get_data() : reverse_get_data(); }
   INT_PTR edit_file::Item::get_delta_length()  { return 0; }



   edit_file::EItemType edit_file::DeleteItem::get_type() {return ItemTypeDelete;}
   DWORD_PTR edit_file::DeleteItem::get_extent() {return 0;}
   DWORD_PTR edit_file::DeleteItem::get_file_extent() {return m_memstorage.GetStorageSize();}
   BYTE * edit_file::DeleteItem::get_data() {return NULL;}
   edit_file::EItemType edit_file::DeleteItem::reverse_get_type() {return ItemTypeInsert;}
   DWORD_PTR edit_file::DeleteItem::reverse_get_extent() {return m_memstorage.GetStorageSize();}
   DWORD_PTR edit_file::DeleteItem::reverse_get_file_extent() {return 0;}
   BYTE * edit_file::DeleteItem::reverse_get_data() {return m_memstorage.GetAllocation();}

   UINT edit_file::DeleteItem::read_ch(edit_file * pfile)
   {
      if(pfile->m_bRootDirection)
      {
         if(pfile->m_dwReadPosition >= m_dwPosition)
         {
            pfile->m_dwReadPosition += m_memstorage.GetStorageSize();
         }
      }
      else
      {
         if(pfile->m_dwReadPosition >= m_dwPosition)
         {
            if(pfile->m_dwReadPosition < (m_dwPosition + m_memstorage.GetStorageSize()))
            {
               return ((byte *)m_memstorage.GetAllocation())[pfile->m_dwReadPosition - m_dwPosition];
            }
            else
            {
               pfile->m_dwReadPosition -= m_memstorage.GetStorageSize();
            }
         }
      }
      return 0xffffffff;
   }

   INT_PTR edit_file::DeleteItem::get_delta_length() {return -m_memstorage.GetStorageSize();};

   edit_file::EItemType edit_file::InsertItem::get_type() {return ItemTypeInsert;}
   DWORD_PTR edit_file::InsertItem::get_extent() {return m_memstorage.GetStorageSize();}
   DWORD_PTR edit_file::InsertItem::get_file_extent() {return 0;};
   BYTE * edit_file::InsertItem::get_data() {return m_memstorage.GetAllocation();}
   edit_file::EItemType edit_file::InsertItem::reverse_get_type() {return ItemTypeDelete;}
   DWORD_PTR edit_file::InsertItem::reverse_get_extent() {return 0;}
   DWORD_PTR edit_file::InsertItem::reverse_get_file_extent() {return m_memstorage.GetStorageSize();}
   BYTE * edit_file::InsertItem::reverse_get_data() {return NULL;}
   INT_PTR edit_file::InsertItem::get_delta_length() {return m_memstorage.GetStorageSize();};

   UINT edit_file::InsertItem::read_ch(edit_file * pfile)
   {
      if(pfile->m_bRootDirection)
      {
         if(pfile->m_dwReadPosition >= m_dwPosition)
         {
            if(pfile->m_dwReadPosition < (m_dwPosition + m_memstorage.GetStorageSize()))
            {
               return ((byte *)m_memstorage.GetAllocation())[pfile->m_dwReadPosition - m_dwPosition];
            }
            else
            {
               pfile->m_dwReadPosition -= m_memstorage.GetStorageSize();
            }
         }
      }
      else
      {
         if(pfile->m_dwReadPosition >= m_dwPosition)
         {
            pfile->m_dwReadPosition += m_memstorage.GetStorageSize();
         }
      }
      return 0xffffffff;
   }




   edit_file::EItemType edit_file::EditItem::get_type() {return ItemTypeEdit;}
   DWORD_PTR edit_file::EditItem::get_extent() {return m_memstorage.GetStorageSize();}
   DWORD_PTR edit_file::EditItem::get_file_extent() {return get_extent();};
   BYTE * edit_file::EditItem::get_data() {return m_memstorage.GetAllocation();}
   edit_file::EItemType edit_file::EditItem::reverse_get_type() {return ItemTypeEdit;}
   DWORD_PTR edit_file::EditItem::reverse_get_extent() {return m_memstorage.GetStorageSize();}
   DWORD_PTR edit_file::EditItem::reverse_get_file_extent() {return get_extent();};
   BYTE * edit_file::EditItem::reverse_get_data() {return m_memstorage.GetAllocation();}
   INT_PTR edit_file::EditItem::get_delta_length() {return 0;};

   UINT edit_file::EditItem::read_ch(edit_file * pfile)
   {
      if(pfile->m_bRootDirection)
      {
         if(pfile->m_dwReadPosition >= m_dwPosition)
         {
            if(pfile->m_dwReadPosition < (m_dwPosition + m_memstorage.GetStorageSize()))
            {
               return ((byte *)m_memstorage.GetAllocation())[pfile->m_dwReadPosition - m_dwPosition];
            }
         }
      }
      else
      {
//         UINT uiRead = 0;
         if(pfile->m_dwReadPosition >= m_dwPosition)
         {
            if(pfile->m_dwReadPosition < (m_dwPosition + m_memstorageReverse.GetStorageSize()))
            {
               return ((byte *)m_memstorageReverse.GetAllocation())[pfile->m_dwReadPosition - m_dwPosition];
            }
         }
      }
      return 0xffffffff;
   }



   edit_file::EItemType edit_file::GroupItem::get_type() {return ItemTypeGroup;}
   DWORD_PTR edit_file::GroupItem::get_extent() {return 0;}
   DWORD_PTR edit_file::GroupItem::get_file_extent() {return 0;};
   BYTE * edit_file::GroupItem::get_data() {return 0;}
   edit_file::EItemType edit_file::GroupItem::reverse_get_type() {return ItemTypeGroup;}
   DWORD_PTR edit_file::GroupItem::reverse_get_extent() {return 0;}
   DWORD_PTR edit_file::GroupItem::reverse_get_file_extent() {return 0;};
   BYTE * edit_file::GroupItem::reverse_get_data() {return 0;}
   INT_PTR edit_file::GroupItem::get_delta_length()
   {
      INT_PTR iLen = 0;
      for(int i = 0; i < get_count(); i++)
      {
         iLen += element_at(i)->get_delta_length();
      }
      return iLen;
   }

   UINT edit_file::GroupItem::read_ch(edit_file * pfile)
   {
      if(pfile->m_bRootDirection)
      {
         for(int i = get_upper_bound(); i >= 0; i--)
         {
            UINT uiReadItem = element_at(i)->read_ch(pfile);
            if(uiReadItem <= 255)
               return uiReadItem;
         }
      }
      else
      {
         for(int i = 0; i < get_count(); i++)
         {
            UINT uiReadItem = element_at(i)->read_ch(pfile);
            if(uiReadItem <= 255)
               return uiReadItem;
         }
      }
      return 0xffffffff;
   }


   edit_file::edit_file(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ex1::tree_data(papp),
      ex1::filesp(papp),
      ::ca::data(papp),
      ex1::tree(papp)
   {
      m_iBranch = 0;
      m_pgroupitem = NULL;

      if(!ex1::tree_data::initialize())
         throw simple_exception();

      if(!ex1::tree::initialize())
         throw simple_exception();

      m_ptreeitem = get_base_item();
      m_ptreeitemFlush = get_base_item();
   }

   edit_file::~edit_file()
   {
      
   }

   void edit_file::SetFile(ex1::file * pfile)
   {
      m_pfile = pfile;
      m_dwFileLength = pfile->get_length();
      m_pfile->seek(0, ::ex1::seek_begin);
      m_dwPosition = 0;
   }

   DWORD_PTR edit_file::read(void *lpBuf, DWORD_PTR nCount)
   {
      byte * buf = (byte *) lpBuf;
      UINT uiRead = 0;
      if(m_dwPosition >= m_dwFileLength)
      {
         return uiRead;
      }
//      DWORD dwPosition = m_dwPosition;
//      DWORD dwFilePosition = m_dwPosition;
//      DWORD dwMaxCount = m_dwFileLength;
//      DWORD dwUpperLimit = m_dwFileLength;
//      int iOffset =0;
      ::ex1::tree_item * ptreeitem;
//      GroupItem * pitemgroup = NULL;
      int_array ia;

      m_bRootDirection = calc_root_direction();

      UINT uiReadItem = 0xffffffff;
      do
      {
l1:
         ptreeitem = m_ptreeitem;
         m_dwReadPosition = m_dwPosition;
         while(nCount > 0 && ptreeitem != NULL && ptreeitem != m_ptreeitemFlush && m_dwPosition < m_dwFileLength)
         {
            Item * pitem = (Item * )ptreeitem->m_pitemdata;
            uiReadItem = pitem->read_ch(this);
            if(uiReadItem <= 255)
            {
               buf[uiRead] = (byte) uiReadItem;
               nCount--;
               uiRead++;
               m_dwPosition++;
               goto l1;
            }
            if(nCount <= 0)
               break;
            ptreeitem = m_bRootDirection ? get_previous(ptreeitem) : get_next(ptreeitem);
         }
         if(nCount > 0 && m_dwPosition < m_dwFileLength)
         {
            m_pfile->seek(m_dwPosition, ::ex1::seek_begin);
            if(!m_pfile->read(&uiReadItem, 1))
               break;
            buf[uiRead] = (byte) uiReadItem;
            nCount--;
            uiRead++;
            m_dwPosition++;
         }
         else
         {
            break;
         }
      } while(nCount > 0 && m_dwPosition < m_dwFileLength);
      return uiRead;
   }


   void edit_file::TreeInsert(Item * pitem)
   {
      if(m_pgroupitem != NULL
        && m_pgroupitem != pitem)
      {
         m_pgroupitem->add(pitem);
         return;
      }
      ex1::tree_item * pitemNew = NULL;
      if(m_ptreeitem != NULL && m_ptreeitem->m_pnext != NULL)
      {
         pitemNew = insert_item(pitem, RelativeFirstChild, m_ptreeitem);
         if(pitemNew != NULL)
         {
            m_ptreeitem = pitemNew;
         }
      }
      else
      {
         pitemNew = insert_item(pitem, RelativeLastSibling, m_ptreeitem);
         if(pitemNew != NULL)
         {
            m_ptreeitem = pitemNew;
         }
      }
      
   }

   void edit_file::write(const void * lpBuf, DWORD_PTR nCount)
   {
      EditItem * pedit;
      pedit = new EditItem; 
      pedit->m_dwPosition = m_dwPosition;
      pedit->m_memstorage.allocate(nCount);
      memcpy(pedit->m_memstorage.GetAllocation(), lpBuf, nCount);
      TreeInsert(pedit);
      m_dwPosition += nCount;
   }

   void edit_file::Insert(const void * lpBuf, DWORD_PTR nCount)
   {
      InsertItem * pinsert;
      pinsert = new InsertItem; 
      pinsert->m_dwPosition = m_dwPosition;
      pinsert->m_memstorage.allocate(nCount);
      memcpy(pinsert->m_memstorage.GetAllocation(), lpBuf, nCount);
      TreeInsert(pinsert);
      m_dwFileLength += nCount;
   }


   void edit_file::Delete(DWORD_PTR uiCount)
   {
      DeleteItem * pdelete;

      uiCount = min(uiCount, get_length() - m_dwPosition);
      if(uiCount == 0)
         return;

      pdelete = new DeleteItem; 
      pdelete->m_dwPosition = m_dwPosition;
      pdelete->m_memstorage.allocate(uiCount);
      seek(m_dwPosition, ::ex1::seek_begin);
      read(pdelete->m_memstorage.GetAllocation(), uiCount);
      TreeInsert(pdelete);
      m_dwFileLength -= uiCount;
      
   }


   DWORD edit_file::GetPosition() const
   {
      return m_dwPosition;
   }

   bool edit_file::IsValid() const
   {
      return true;
   }

   INT_PTR edit_file::seek(INT_PTR lOff, UINT nFrom)
   {
      ASSERT(IsValid());
      ASSERT(nFrom == ::ex1::seek_begin || nFrom == ::ex1::seek_end || nFrom == ::ex1::seek_current);
      ASSERT(::ex1::seek_begin == FILE_BEGIN && ::ex1::seek_end == FILE_END && ::ex1::seek_current == FILE_CURRENT);

      DWORD_PTR dwNew = (DWORD) -1;

      switch(nFrom)
      {
      case ::ex1::seek_begin:
         dwNew = lOff;
         break;
      case ::ex1::seek_end:
         dwNew = get_length() - lOff;
         break;
      case ::ex1::seek_current:
         if(lOff < 0)
         {
            dwNew = m_dwPosition + lOff;
            if(dwNew > m_dwPosition)
               dwNew = 0;
         }
         else
         {
            dwNew = m_dwPosition + lOff;
         }
         
         break;
      default:
         return -1;
      }

      m_dwPosition = dwNew;

      return dwNew;
   }


   DWORD edit_file::get_length() const
   {
      return m_dwFileLength;
   }

   void edit_file::Flush()
   {
      string strTimeFile;

      strTimeFile = System.file().time_square();

      ex1::filesp spfile(get_app());
      if(!spfile->open(strTimeFile, ::ex1::file::type_binary | ::ex1::file::mode_read_write | ::ex1::file::mode_create))
         return;

      Save(spfile);

      char buf[4096];
      UINT uiRead;
      m_pfile->SetLength(0);
      spfile->seek(0, ::ex1::seek_begin);
      while((uiRead = spfile->read(buf, sizeof(buf))) > 0)
      {
         m_pfile->write(buf, uiRead);
      }
      m_pfile->Flush();
      m_dwFileLength = m_pfile->get_length();
      m_ptreeitemFlush = m_ptreeitem;
   }

   bool edit_file::Save(ex1::file & file)
   {
      char buf[4096];
      UINT uiRead;
      file.SetLength(0);
      seek(0, ::ex1::seek_begin);
      while((uiRead = read(buf, sizeof(buf))) > 0)
      {
         file.write(buf, uiRead);
      }
      file.Flush();
      file.close();
      return true;
   }

   bool edit_file::Save_N_to_CRLF(ex1::file & file)
   {
      char buf[4096];
      string str;
      UINT uiRead;
      file.SetLength(0);
      seek(0, ::ex1::seek_begin);
      while((uiRead = read(buf, sizeof(buf))) > 0)
      {
         buf[uiRead] = '\0';
         str = buf;
         str.replace("\n", "\r\n");
         file.write(str, str.get_length());
      }
      file.Flush();
      file.close();
      return true;
   }


   bool edit_file::CanUndo()
   {
      return m_ptreeitem != get_base_item();
   }

   bool edit_file::CanRedo()
   {
      return m_iBranch < m_ptreeitem->get_expandable_children_count() 
         || m_ptreeitem->get_next(false, false) != NULL;
   }

   count edit_file::GetRedoBranchCount()
   {
      if(m_ptreeitem == NULL)
         return 1;
      else
         return   m_ptreeitem->get_expandable_children_count() 
           + (m_ptreeitem->m_pnext != NULL ? 1 : 0)
           + (m_ptreeitem->m_pchild != NULL ? 1 : 0);
   }

   bool edit_file::Undo()
   {
      if(!CanUndo())
         return false;

      m_dwFileLength -= ((Item *)m_ptreeitem->m_pitemdata)->get_delta_length();
      m_ptreeitem = get_previous(m_ptreeitem);

      return true;
   }

   bool edit_file::Redo()
   {
      if(m_iBranch < 0 || m_iBranch >= GetRedoBranchCount())
      {
         return false;
      }
//      Item * pitem = NULL;
      ::ex1::tree_item * ptreeitem;
      if(m_iBranch < m_ptreeitem->get_expandable_children_count())
      {
         ptreeitem = m_ptreeitem->get_expandable_child(m_iBranch);
      }
      else 
         ptreeitem = get_next(m_ptreeitem);
      if(ptreeitem == NULL)
         return false;
      m_dwFileLength += (( Item * ) ptreeitem->m_pitemdata)->get_delta_length();
      m_ptreeitem = ptreeitem;
      return true;
   }

   void edit_file::MacroBegin()
   {
      GroupItem * pgroupitem = new GroupItem;
      pgroupitem->m_pgroupitem = m_pgroupitem;
      m_pgroupitem = pgroupitem;
   }

   void edit_file::MacroEnd()
   {
      if(m_pgroupitem == NULL)
      {
         ASSERT(FALSE);
         return;
      }
      if(m_pgroupitem->m_pgroupitem == NULL)
      {
         TreeInsert(m_pgroupitem);
      }
      m_pgroupitem = m_pgroupitem->m_pgroupitem;
   }



   bool edit_file::calc_root_direction()
   {
      ::ex1::tree_item * ptreeitem;
      if(m_ptreeitem == m_ptreeitemFlush)
         return false;
      for(ptreeitem  = m_ptreeitem; 
          ptreeitem != m_ptreeitemFlush && ptreeitem != get_base_item() && ptreeitem != NULL; 
          ptreeitem  = get_previous(ptreeitem))
      {
      }
      return ptreeitem == m_ptreeitemFlush;
   }


   ::ex1::tree_item * edit_file::get_previous(::ex1::tree_item * pitem)
   {
      if(pitem->m_pprevious != NULL)
         return pitem->m_pprevious;
      else
         return pitem->m_pparent;
   }

   ::ex1::tree_item * edit_file::get_next(::ex1::tree_item * pitem, bool bChild)
   {
      if(bChild && pitem->m_pchild != NULL)
         return pitem->m_pchild;
      else if(pitem->m_pnext != NULL)
         return pitem->m_pnext;
      else if(pitem->m_pparent != NULL)
         return get_next(pitem->m_pparent, false);
      else
         return NULL;
   }



   tree_item_data * edit_file::on_allocate_item()
   {
      return new Item;
   }
      
   void edit_file::on_delete_item(tree_item_data * pitem)
   {
      delete (Item *) pitem;
   }


} // namespace ex1