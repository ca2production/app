#include "StdAfx.h"

namespace colorertake5
{

Outliner::Outliner(base_editor *baseEditor, class region *searchRegion){
  this->searchRegion = searchRegion;
  modifiedLine = -1;
  this->baseEditor = baseEditor;
  baseEditor->addRegionHandler(this);
  baseEditor->addEditorListener(this);
}

Outliner::~Outliner(){
  baseEditor->removeRegionHandler(this);
  baseEditor->removeEditorListener(this);

  for(int idx = 0; idx < outline.get_size(); idx++)
    delete outline.element_at(idx);
}



OutlineItem *Outliner::getItem(int idx){
  return outline.element_at(idx);
}


int Outliner::itemCount(){
  return outline.get_size();
}


int Outliner::manageTree(base_array<int> &treeStack, int newLevel){
  while(treeStack.get_size() > 0 && newLevel < treeStack.last_element())
    treeStack.remove_at(treeStack.get_size()-1);
  if (treeStack.get_size() == 0 || newLevel > treeStack.last_element()){
    treeStack.add(newLevel);
    return treeStack.get_size()-1;
  };
  if (newLevel == treeStack.last_element()) return treeStack.get_size()-1;
  return 0;
}


bool Outliner::isOutlined(class region*region){
  return region->hasParent(searchRegion);
}

void Outliner::modifyEvent(int topLine){
  int new_size;
  for(new_size = outline.get_size()-1; new_size >= 0; new_size--){
    if (outline.element_at(new_size)->lno < topLine) break;
    delete outline.element_at(new_size);
  };
  outline.set_size(new_size+1);

  modifiedLine = topLine;
}

void Outliner::startParsing(int lno)
{
   UNREFERENCED_PARAMETER(lno);
   curLevel = 0;
}

void Outliner::endParsing(int lno)
{
   if (modifiedLine < lno)
   {
      modifiedLine = lno+1;
   }
   curLevel = 0;
}

void Outliner::clearLine(int lno, const char * line)
{
   UNREFERENCED_PARAMETER(lno);
   UNREFERENCED_PARAMETER(line);
   lineIsEmpty = true;
}

void Outliner::addRegion(int lno, const char * line, int sx, int ex, class region *region){
  if (lno < modifiedLine) return;
  if (!isOutlined(region)) return;

  string itemLabel = string(&line[sx], ex-sx);

  if (lineIsEmpty)
  {
    outline.add(new OutlineItem(lno, sx, curLevel, itemLabel, region));
  }
  else
  {
    OutlineItem *thisItem = outline.last_element();
    if (itemLabel != NULL && thisItem->token != NULL && thisItem->lno == lno)
      thisItem->token += itemLabel;
  };
  lineIsEmpty = false;
}

void Outliner::enterScheme(int lno, const char *line, int sx, int ex, class region * region, class scheme * scheme)
{
   UNREFERENCED_PARAMETER(lno);
   UNREFERENCED_PARAMETER(line);
   UNREFERENCED_PARAMETER(sx);
   UNREFERENCED_PARAMETER(ex);
   UNREFERENCED_PARAMETER(region);
   UNREFERENCED_PARAMETER(scheme);
  
   curLevel++;
}

void Outliner::leaveScheme(int lno, const char *line, int sx, int ex, class region * region, class scheme * scheme)
{
   UNREFERENCED_PARAMETER(lno);
   UNREFERENCED_PARAMETER(line);
   UNREFERENCED_PARAMETER(sx);
   UNREFERENCED_PARAMETER(ex);
   UNREFERENCED_PARAMETER(region);
   UNREFERENCED_PARAMETER(scheme);

   curLevel--;
}

} // namespace colorertake5

/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Colorer Library.
 *
 * The Initial Developer of the Original Code is
 * Cail Lomecb <cail@nm.ru>.
 * Portions created by the Initial Developer are Copyright (C) 1999-2005
 * the Initial Developer. 
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
