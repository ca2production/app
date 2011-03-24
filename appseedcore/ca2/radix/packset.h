#pragma once

template <class ID_TYPE, class ARG_ID_TYPE, class ITEM_TYPE, class ARG_ITEM_TYPE, 
   class ARRAY = base_array < ITEM_TYPE, ARG_ITEM_TYPE > >
class packset :
   virtual public ::collection::map < ID_TYPE, ARG_ID_TYPE, ARRAY, ARRAY >
{
public:
   packset();
   void pack(ARG_ID_TYPE id, ARG_ITEM_TYPE item);
   count get_pack_count();
   count get_item_count();
};

template <class ID_TYPE, class ARG_ID_TYPE, class ITEM_TYPE, class ARG_ITEM_TYPE, class ARRAY >
packset <ID_TYPE, ARG_ID_TYPE, ITEM_TYPE, ARG_ITEM_TYPE, ARRAY> ::
packset()
{
}


template <class ID_TYPE, class ARG_ID_TYPE, class ITEM_TYPE, class ARG_ITEM_TYPE, class ARRAY >
void packset <ID_TYPE, ARG_ID_TYPE, ITEM_TYPE, ARG_ITEM_TYPE, ARRAY> ::
pack(ARG_ID_TYPE id, ARG_ITEM_TYPE item)
{
   operator[](id).add(item);
}


template <class ID_TYPE, class ARG_ID_TYPE, class ITEM_TYPE, class ARG_ITEM_TYPE, class ARRAY >
count packset <ID_TYPE, ARG_ID_TYPE, ITEM_TYPE, ARG_ITEM_TYPE, ARRAY> ::
get_pack_count()
{
   return get_size();
}

template <class ID_TYPE, class ARG_ID_TYPE, class ITEM_TYPE, class ARG_ITEM_TYPE, class ARRAY >
count packset <ID_TYPE, ARG_ID_TYPE, ITEM_TYPE, ARG_ITEM_TYPE, ARRAY> ::
get_item_count()
{
   count count = 0;
   pair * p = PGetFirstAssoc();
   while(p != NULL)
   {
      count += p->m_value.get_count();
      p = PGetNextAssoc(p);
   }
   return count;
}
