#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE path_view :
      virtual public ::user::show < ::user::plain_edit >,
      virtual public ::filemanager::impact
   {
   public:

      bool m_bVoidSync;



       path_view(::aura::application * papp);


      virtual void _001OnAfterChangeText(::action::context actioncontext);


      void on_update(::user::impact * pSender, LPARAM lHint, object* phint);

      virtual void _001OnDraw(::draw2d::dib * pdib);

      virtual void browse_sync(::action::context actioncontext);

   };


} // namespace filemanager




