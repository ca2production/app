#pragma once

namespace user
{

   class tab;

   class CLASS_DECL_ca tab_callback
   {
   public:
      virtual void _001OnTabClick(int iTab);
      virtual bool _001IsAddTab(int iTab);
      virtual ::user::interaction * _001GetTabWnd(int iTab);

      virtual void on_show_view(tab * pinterface);

      virtual void _001OnDropTab(int iTab, e_position eposition);

      virtual void _001DropTargetWindowInitialize(tab * pinterface);
      virtual void _001DropTargetWindowRelay(tab * pinterface);
      virtual void _001DropTargetWindowFinalize(tab * pinterface);

      tab_callback();
      virtual ~tab_callback();
   };

} // namespace user