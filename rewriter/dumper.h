// 
// Generated from nm output of classvisitor, looking for ::Visit symbols.  Then in vim:
//
// :,$ s/bool \(.*\)/&Z{Z   cout << endl << "&" << endl ;ZZ   v->dump() ;ZZ   return true ;Z}ZZ/
// :,$ !tr Z '\n'
//
// Since the XML AST dumper that apparently once existed has been deleted, this provides a poor man's version, also implicitly
// showing what ASTVisitor methods one would wish to override to find the desired source code info.
//

bool VisitAbstractConditionalOperator( AbstractConditionalOperator * v )
{
   cout << endl << "bool VisitAbstractConditionalOperator( AbstractConditionalOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitAccessSpecDecl( AccessSpecDecl * v )
{
   cout << endl << "bool VisitAccessSpecDecl( AccessSpecDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitAddrLabelExpr( AddrLabelExpr * v )
{
   cout << endl << "bool VisitAddrLabelExpr( AddrLabelExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitArraySubscriptExpr( ArraySubscriptExpr * v )
{
   cout << endl << "bool VisitArraySubscriptExpr( ArraySubscriptExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitArrayType( ArrayType * v )
{
   cout << endl << "bool VisitArrayType( ArrayType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitArrayTypeTraitExpr( ArrayTypeTraitExpr * v )
{
   cout << endl << "bool VisitArrayTypeTraitExpr( ArrayTypeTraitExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitAsmStmt( AsmStmt * v )
{
   cout << endl << "bool VisitAsmStmt( AsmStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitAsTypeExpr( AsTypeExpr * v )
{
   cout << endl << "bool VisitAsTypeExpr( AsTypeExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitAtomicExpr( AtomicExpr * v )
{
   cout << endl << "bool VisitAtomicExpr( AtomicExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitAtomicType( AtomicType * v )
{
   cout << endl << "bool VisitAtomicType( AtomicType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitAttributedStmt( AttributedStmt * v )
{
   cout << endl << "bool VisitAttributedStmt( AttributedStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitAttributedType( AttributedType * v )
{
   cout << endl << "bool VisitAttributedType( AttributedType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitAutoType( AutoType * v )
{
   cout << endl << "bool VisitAutoType( AutoType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinAddAssign( CompoundAssignOperator * v )
{
   cout << endl << "bool VisitBinAddAssign( CompoundAssignOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinAdd( BinaryOperator * v )
{
   cout << endl << "bool VisitBinAdd( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinAndAssign( CompoundAssignOperator * v )
{
   cout << endl << "bool VisitBinAndAssign( CompoundAssignOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinAnd( BinaryOperator * v )
{
   cout << endl << "bool VisitBinAnd( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinaryConditionalOperator( BinaryConditionalOperator * v )
{
   cout << endl << "bool VisitBinaryConditionalOperator( BinaryConditionalOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinaryOperator( BinaryOperator * v )
{
   cout << endl << "bool VisitBinaryOperator( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinaryTypeTraitExpr( BinaryTypeTraitExpr * v )
{
   cout << endl << "bool VisitBinaryTypeTraitExpr( BinaryTypeTraitExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinAssign( BinaryOperator * v )
{
   cout << endl << "bool VisitBinAssign( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinComma( BinaryOperator * v )
{
   cout << endl << "bool VisitBinComma( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinDivAssign( CompoundAssignOperator * v )
{
   cout << endl << "bool VisitBinDivAssign( CompoundAssignOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinDiv( BinaryOperator * v )
{
   cout << endl << "bool VisitBinDiv( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinEQ( BinaryOperator * v )
{
   cout << endl << "bool VisitBinEQ( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinGE( BinaryOperator * v )
{
   cout << endl << "bool VisitBinGE( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinGT( BinaryOperator * v )
{
   cout << endl << "bool VisitBinGT( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinLAnd( BinaryOperator * v )
{
   cout << endl << "bool VisitBinLAnd( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinLE( BinaryOperator * v )
{
   cout << endl << "bool VisitBinLE( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinLOr( BinaryOperator * v )
{
   cout << endl << "bool VisitBinLOr( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinLT( BinaryOperator * v )
{
   cout << endl << "bool VisitBinLT( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinMulAssign( CompoundAssignOperator * v )
{
   cout << endl << "bool VisitBinMulAssign( CompoundAssignOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinMul( BinaryOperator * v )
{
   cout << endl << "bool VisitBinMul( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinNE( BinaryOperator * v )
{
   cout << endl << "bool VisitBinNE( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinOrAssign( CompoundAssignOperator * v )
{
   cout << endl << "bool VisitBinOrAssign( CompoundAssignOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinOr( BinaryOperator * v )
{
   cout << endl << "bool VisitBinOr( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinPtrMemD( BinaryOperator * v )
{
   cout << endl << "bool VisitBinPtrMemD( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinPtrMemI( BinaryOperator * v )
{
   cout << endl << "bool VisitBinPtrMemI( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinRemAssign( CompoundAssignOperator * v )
{
   cout << endl << "bool VisitBinRemAssign( CompoundAssignOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinRem( BinaryOperator * v )
{
   cout << endl << "bool VisitBinRem( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinShlAssign( CompoundAssignOperator * v )
{
   cout << endl << "bool VisitBinShlAssign( CompoundAssignOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinShl( BinaryOperator * v )
{
   cout << endl << "bool VisitBinShl( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinShrAssign( CompoundAssignOperator * v )
{
   cout << endl << "bool VisitBinShrAssign( CompoundAssignOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinShr( BinaryOperator * v )
{
   cout << endl << "bool VisitBinShr( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinSubAssign( CompoundAssignOperator * v )
{
   cout << endl << "bool VisitBinSubAssign( CompoundAssignOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinSub( BinaryOperator * v )
{
   cout << endl << "bool VisitBinSub( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinXorAssign( CompoundAssignOperator * v )
{
   cout << endl << "bool VisitBinXorAssign( CompoundAssignOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBinXor( BinaryOperator * v )
{
   cout << endl << "bool VisitBinXor( BinaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBlockDecl( BlockDecl * v )
{
   cout << endl << "bool VisitBlockDecl( BlockDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBlockExpr( BlockExpr * v )
{
   cout << endl << "bool VisitBlockExpr( BlockExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBlockPointerType( BlockPointerType * v )
{
   cout << endl << "bool VisitBlockPointerType( BlockPointerType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBreakStmt( BreakStmt * v )
{
   cout << endl << "bool VisitBreakStmt( BreakStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitBuiltinType( BuiltinType * v )
{
   cout << endl << "bool VisitBuiltinType( BuiltinType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCallExpr( CallExpr * v )
{
   cout << endl << "bool VisitCallExpr( CallExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCaseStmt( CaseStmt * v )
{
   cout << endl << "bool VisitCaseStmt( CaseStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCastExpr( CastExpr * v )
{
   cout << endl << "bool VisitCastExpr( CastExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCharacterLiteral( CharacterLiteral * v )
{
   cout << endl << "bool VisitCharacterLiteral( CharacterLiteral * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitChooseExpr( ChooseExpr * v )
{
   cout << endl << "bool VisitChooseExpr( ChooseExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitClassScopeFunctionSpecializationDecl( ClassScopeFunctionSpecializationDecl * v )
{
   cout << endl << "bool VisitClassScopeFunctionSpecializationDecl( ClassScopeFunctionSpecializationDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitClassTemplateDecl( ClassTemplateDecl * v )
{
   cout << endl << "bool VisitClassTemplateDecl( ClassTemplateDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitClassTemplatePartialSpecializationDecl( ClassTemplatePartialSpecializationDecl * v )
{
   cout << endl << "bool VisitClassTemplatePartialSpecializationDecl( ClassTemplatePartialSpecializationDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitClassTemplateSpecializationDecl( ClassTemplateSpecializationDecl * v )
{
   cout << endl << "bool VisitClassTemplateSpecializationDecl( ClassTemplateSpecializationDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitComplexType( ComplexType * v )
{
   cout << endl << "bool VisitComplexType( ComplexType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCompoundAssignOperator( CompoundAssignOperator * v )
{
   cout << endl << "bool VisitCompoundAssignOperator( CompoundAssignOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCompoundLiteralExpr( CompoundLiteralExpr * v )
{
   cout << endl << "bool VisitCompoundLiteralExpr( CompoundLiteralExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCompoundStmt( CompoundStmt * v )
{
   cout << endl << "bool VisitCompoundStmt( CompoundStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitConditionalOperator( ConditionalOperator * v )
{
   cout << endl << "bool VisitConditionalOperator( ConditionalOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitConstantArrayType( ConstantArrayType * v )
{
   cout << endl << "bool VisitConstantArrayType( ConstantArrayType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitContinueStmt( ContinueStmt * v )
{
   cout << endl << "bool VisitContinueStmt( ContinueStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCStyleCastExpr( CStyleCastExpr * v )
{
   cout << endl << "bool VisitCStyleCastExpr( CStyleCastExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCUDAKernelCallExpr( CUDAKernelCallExpr * v )
{
   cout << endl << "bool VisitCUDAKernelCallExpr( CUDAKernelCallExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXBindTemporaryExpr( CXXBindTemporaryExpr * v )
{
   cout << endl << "bool VisitCXXBindTemporaryExpr( CXXBindTemporaryExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXBoolLiteralExpr( CXXBoolLiteralExpr * v )
{
   cout << endl << "bool VisitCXXBoolLiteralExpr( CXXBoolLiteralExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXCatchStmt( CXXCatchStmt * v )
{
   cout << endl << "bool VisitCXXCatchStmt( CXXCatchStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXConstCastExpr( CXXConstCastExpr * v )
{
   cout << endl << "bool VisitCXXConstCastExpr( CXXConstCastExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXConstructExpr( CXXConstructExpr * v )
{
   cout << endl << "bool VisitCXXConstructExpr( CXXConstructExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXConstructorDecl( CXXConstructorDecl * v )
{
   cout << endl << "bool VisitCXXConstructorDecl( CXXConstructorDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXConversionDecl( CXXConversionDecl * v )
{
   cout << endl << "bool VisitCXXConversionDecl( CXXConversionDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXDefaultArgExpr( CXXDefaultArgExpr * v )
{
   cout << endl << "bool VisitCXXDefaultArgExpr( CXXDefaultArgExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXDeleteExpr( CXXDeleteExpr * v )
{
   cout << endl << "bool VisitCXXDeleteExpr( CXXDeleteExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXDependentScopeMemberExpr( CXXDependentScopeMemberExpr * v )
{
   cout << endl << "bool VisitCXXDependentScopeMemberExpr( CXXDependentScopeMemberExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXDestructorDecl( CXXDestructorDecl * v )
{
   cout << endl << "bool VisitCXXDestructorDecl( CXXDestructorDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXDynamicCastExpr( CXXDynamicCastExpr * v )
{
   cout << endl << "bool VisitCXXDynamicCastExpr( CXXDynamicCastExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXForRangeStmt( CXXForRangeStmt * v )
{
   cout << endl << "bool VisitCXXForRangeStmt( CXXForRangeStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXFunctionalCastExpr( CXXFunctionalCastExpr * v )
{
   cout << endl << "bool VisitCXXFunctionalCastExpr( CXXFunctionalCastExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXMemberCallExpr( CXXMemberCallExpr * v )
{
   cout << endl << "bool VisitCXXMemberCallExpr( CXXMemberCallExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXMethodDecl( CXXMethodDecl * v )
{
   cout << endl << "bool VisitCXXMethodDecl( CXXMethodDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXNamedCastExpr( CXXNamedCastExpr * v )
{
   cout << endl << "bool VisitCXXNamedCastExpr( CXXNamedCastExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXNewExpr( CXXNewExpr * v )
{
   cout << endl << "bool VisitCXXNewExpr( CXXNewExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXNoexceptExpr( CXXNoexceptExpr * v )
{
   cout << endl << "bool VisitCXXNoexceptExpr( CXXNoexceptExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXNullPtrLiteralExpr( CXXNullPtrLiteralExpr * v )
{
   cout << endl << "bool VisitCXXNullPtrLiteralExpr( CXXNullPtrLiteralExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXOperatorCallExpr( CXXOperatorCallExpr * v )
{
   cout << endl << "bool VisitCXXOperatorCallExpr( CXXOperatorCallExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXPseudoDestructorExpr( CXXPseudoDestructorExpr * v )
{
   cout << endl << "bool VisitCXXPseudoDestructorExpr( CXXPseudoDestructorExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXReinterpretCastExpr( CXXReinterpretCastExpr * v )
{
   cout << endl << "bool VisitCXXReinterpretCastExpr( CXXReinterpretCastExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXScalarValueInitExpr( CXXScalarValueInitExpr * v )
{
   cout << endl << "bool VisitCXXScalarValueInitExpr( CXXScalarValueInitExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXStaticCastExpr( CXXStaticCastExpr * v )
{
   cout << endl << "bool VisitCXXStaticCastExpr( CXXStaticCastExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXTemporaryObjectExpr( CXXTemporaryObjectExpr * v )
{
   cout << endl << "bool VisitCXXTemporaryObjectExpr( CXXTemporaryObjectExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXThisExpr( CXXThisExpr * v )
{
   cout << endl << "bool VisitCXXThisExpr( CXXThisExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXThrowExpr( CXXThrowExpr * v )
{
   cout << endl << "bool VisitCXXThrowExpr( CXXThrowExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXTryStmt( CXXTryStmt * v )
{
   cout << endl << "bool VisitCXXTryStmt( CXXTryStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXTypeidExpr( CXXTypeidExpr * v )
{
   cout << endl << "bool VisitCXXTypeidExpr( CXXTypeidExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXUnresolvedConstructExpr( CXXUnresolvedConstructExpr * v )
{
   cout << endl << "bool VisitCXXUnresolvedConstructExpr( CXXUnresolvedConstructExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitCXXUuidofExpr( CXXUuidofExpr * v )
{
   cout << endl << "bool VisitCXXUuidofExpr( CXXUuidofExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDeclaratorDecl( DeclaratorDecl * v )
{
   cout << endl << "bool VisitDeclaratorDecl( DeclaratorDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDecl( Decl * v )
{
   cout << endl << "bool VisitDecl( Decl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDeclRefExpr( DeclRefExpr * v )
{
   cout << endl << "bool VisitDeclRefExpr( DeclRefExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDeclStmt( DeclStmt * v )
{
   cout << endl << "bool VisitDeclStmt( DeclStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDecltypeType( DecltypeType * v )
{
   cout << endl << "bool VisitDecltypeType( DecltypeType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDefaultStmt( DefaultStmt * v )
{
   cout << endl << "bool VisitDefaultStmt( DefaultStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDependentNameType( DependentNameType * v )
{
   cout << endl << "bool VisitDependentNameType( DependentNameType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDependentScopeDeclRefExpr( DependentScopeDeclRefExpr * v )
{
   cout << endl << "bool VisitDependentScopeDeclRefExpr( DependentScopeDeclRefExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDependentSizedArrayType( DependentSizedArrayType * v )
{
   cout << endl << "bool VisitDependentSizedArrayType( DependentSizedArrayType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDependentSizedExtVectorType( DependentSizedExtVectorType * v )
{
   cout << endl << "bool VisitDependentSizedExtVectorType( DependentSizedExtVectorType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDependentTemplateSpecializationType( DependentTemplateSpecializationType * v )
{
   cout << endl << "bool VisitDependentTemplateSpecializationType( DependentTemplateSpecializationType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDesignatedInitExpr( DesignatedInitExpr * v )
{
   cout << endl << "bool VisitDesignatedInitExpr( DesignatedInitExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitDoStmt( DoStmt * v )
{
   cout << endl << "bool VisitDoStmt( DoStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitElaboratedType( ElaboratedType * v )
{
   cout << endl << "bool VisitElaboratedType( ElaboratedType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitEnumConstantDecl( EnumConstantDecl * v )
{
   cout << endl << "bool VisitEnumConstantDecl( EnumConstantDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitEnumDecl( EnumDecl * v )
{
   cout << endl << "bool VisitEnumDecl( EnumDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitEnumType( EnumType * v )
{
   cout << endl << "bool VisitEnumType( EnumType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitExplicitCastExpr( ExplicitCastExpr * v )
{
   cout << endl << "bool VisitExplicitCastExpr( ExplicitCastExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitExpressionTraitExpr( ExpressionTraitExpr * v )
{
   cout << endl << "bool VisitExpressionTraitExpr( ExpressionTraitExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitExpr( Expr * v )
{
   cout << endl << "bool VisitExpr( Expr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitExprWithCleanups( ExprWithCleanups * v )
{
   cout << endl << "bool VisitExprWithCleanups( ExprWithCleanups * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitExtVectorElementExpr( ExtVectorElementExpr * v )
{
   cout << endl << "bool VisitExtVectorElementExpr( ExtVectorElementExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitExtVectorType( ExtVectorType * v )
{
   cout << endl << "bool VisitExtVectorType( ExtVectorType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitFileScopeAsmDecl( FileScopeAsmDecl * v )
{
   cout << endl << "bool VisitFileScopeAsmDecl( FileScopeAsmDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitFloatingLiteral( FloatingLiteral * v )
{
   cout << endl << "bool VisitFloatingLiteral( FloatingLiteral * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitForStmt( ForStmt * v )
{
   cout << endl << "bool VisitForStmt( ForStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitFriendDecl( FriendDecl * v )
{
   cout << endl << "bool VisitFriendDecl( FriendDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitFriendTemplateDecl( FriendTemplateDecl * v )
{
   cout << endl << "bool VisitFriendTemplateDecl( FriendTemplateDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitFunctionDecl( FunctionDecl * v )
{
   cout << endl << "bool VisitFunctionDecl( FunctionDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitFunctionNoProtoType( FunctionNoProtoType * v )
{
   cout << endl << "bool VisitFunctionNoProtoType( FunctionNoProtoType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitFunctionParmPackExpr( FunctionParmPackExpr * v )
{
   cout << endl << "bool VisitFunctionParmPackExpr( FunctionParmPackExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitFunctionProtoType( FunctionProtoType * v )
{
   cout << endl << "bool VisitFunctionProtoType( FunctionProtoType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitFunctionTemplateDecl( FunctionTemplateDecl * v )
{
   cout << endl << "bool VisitFunctionTemplateDecl( FunctionTemplateDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitFunctionType( FunctionType * v )
{
   cout << endl << "bool VisitFunctionType( FunctionType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitGCCAsmStmt( GCCAsmStmt * v )
{
   cout << endl << "bool VisitGCCAsmStmt( GCCAsmStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitGenericSelectionExpr( GenericSelectionExpr * v )
{
   cout << endl << "bool VisitGenericSelectionExpr( GenericSelectionExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitGNUNullExpr( GNUNullExpr * v )
{
   cout << endl << "bool VisitGNUNullExpr( GNUNullExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitGotoStmt( GotoStmt * v )
{
   cout << endl << "bool VisitGotoStmt( GotoStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitIfStmt( IfStmt * v )
{
   cout << endl << "bool VisitIfStmt( IfStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitImaginaryLiteral( ImaginaryLiteral * v )
{
   cout << endl << "bool VisitImaginaryLiteral( ImaginaryLiteral * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitImplicitCastExpr( ImplicitCastExpr * v )
{
   cout << endl << "bool VisitImplicitCastExpr( ImplicitCastExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitImplicitParamDecl( ImplicitParamDecl * v )
{
   cout << endl << "bool VisitImplicitParamDecl( ImplicitParamDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitImplicitValueInitExpr( ImplicitValueInitExpr * v )
{
   cout << endl << "bool VisitImplicitValueInitExpr( ImplicitValueInitExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitImportDecl( ImportDecl * v )
{
   cout << endl << "bool VisitImportDecl( ImportDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitIncompleteArrayType( IncompleteArrayType * v )
{
   cout << endl << "bool VisitIncompleteArrayType( IncompleteArrayType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitIndirectFieldDecl( IndirectFieldDecl * v )
{
   cout << endl << "bool VisitIndirectFieldDecl( IndirectFieldDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitIndirectGotoStmt( IndirectGotoStmt * v )
{
   cout << endl << "bool VisitIndirectGotoStmt( IndirectGotoStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitInitListExpr( InitListExpr * v )
{
   cout << endl << "bool VisitInitListExpr( InitListExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitInjectedClassNameType( InjectedClassNameType * v )
{
   cout << endl << "bool VisitInjectedClassNameType( InjectedClassNameType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitIntegerLiteral( IntegerLiteral * v )
{
   cout << endl << "bool VisitIntegerLiteral( IntegerLiteral * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitLabelDecl( LabelDecl * v )
{
   cout << endl << "bool VisitLabelDecl( LabelDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitLabelStmt( LabelStmt * v )
{
   cout << endl << "bool VisitLabelStmt( LabelStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitLambdaExpr( LambdaExpr * v )
{
   cout << endl << "bool VisitLambdaExpr( LambdaExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitLinkageSpecDecl( LinkageSpecDecl * v )
{
   cout << endl << "bool VisitLinkageSpecDecl( LinkageSpecDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitLValueReferenceType( LValueReferenceType * v )
{
   cout << endl << "bool VisitLValueReferenceType( LValueReferenceType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitMaterializeTemporaryExpr( MaterializeTemporaryExpr * v )
{
   cout << endl << "bool VisitMaterializeTemporaryExpr( MaterializeTemporaryExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitMemberExpr( MemberExpr * v )
{
   cout << endl << "bool VisitMemberExpr( MemberExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitMemberPointerType( MemberPointerType * v )
{
   cout << endl << "bool VisitMemberPointerType( MemberPointerType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitMSAsmStmt( MSAsmStmt * v )
{
   cout << endl << "bool VisitMSAsmStmt( MSAsmStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitMSDependentExistsStmt( MSDependentExistsStmt * v )
{
   cout << endl << "bool VisitMSDependentExistsStmt( MSDependentExistsStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitNamedDecl( NamedDecl * v )
{
   cout << endl << "bool VisitNamedDecl( NamedDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitNamespaceAliasDecl( NamespaceAliasDecl * v )
{
   cout << endl << "bool VisitNamespaceAliasDecl( NamespaceAliasDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitNamespaceDecl( NamespaceDecl * v )
{
   cout << endl << "bool VisitNamespaceDecl( NamespaceDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitNonTypeTemplateParmDecl( NonTypeTemplateParmDecl * v )
{
   cout << endl << "bool VisitNonTypeTemplateParmDecl( NonTypeTemplateParmDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitNullStmt( NullStmt * v )
{
   cout << endl << "bool VisitNullStmt( NullStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCArrayLiteral( ObjCArrayLiteral * v )
{
   cout << endl << "bool VisitObjCArrayLiteral( ObjCArrayLiteral * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCAtCatchStmt( ObjCAtCatchStmt * v )
{
   cout << endl << "bool VisitObjCAtCatchStmt( ObjCAtCatchStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCAtDefsFieldDecl( ObjCAtDefsFieldDecl * v )
{
   cout << endl << "bool VisitObjCAtDefsFieldDecl( ObjCAtDefsFieldDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCAtFinallyStmt( ObjCAtFinallyStmt * v )
{
   cout << endl << "bool VisitObjCAtFinallyStmt( ObjCAtFinallyStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCAtSynchronizedStmt( ObjCAtSynchronizedStmt * v )
{
   cout << endl << "bool VisitObjCAtSynchronizedStmt( ObjCAtSynchronizedStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCAtThrowStmt( ObjCAtThrowStmt * v )
{
   cout << endl << "bool VisitObjCAtThrowStmt( ObjCAtThrowStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCAtTryStmt( ObjCAtTryStmt * v )
{
   cout << endl << "bool VisitObjCAtTryStmt( ObjCAtTryStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCAutoreleasePoolStmt( ObjCAutoreleasePoolStmt * v )
{
   cout << endl << "bool VisitObjCAutoreleasePoolStmt( ObjCAutoreleasePoolStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCBoolLiteralExpr( ObjCBoolLiteralExpr * v )
{
   cout << endl << "bool VisitObjCBoolLiteralExpr( ObjCBoolLiteralExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCBoxedExpr( ObjCBoxedExpr * v )
{
   cout << endl << "bool VisitObjCBoxedExpr( ObjCBoxedExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCBridgedCastExpr( ObjCBridgedCastExpr * v )
{
   cout << endl << "bool VisitObjCBridgedCastExpr( ObjCBridgedCastExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCCategoryDecl( ObjCCategoryDecl * v )
{
   cout << endl << "bool VisitObjCCategoryDecl( ObjCCategoryDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCCategoryImplDecl( ObjCCategoryImplDecl * v )
{
   cout << endl << "bool VisitObjCCategoryImplDecl( ObjCCategoryImplDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCCompatibleAliasDecl( ObjCCompatibleAliasDecl * v )
{
   cout << endl << "bool VisitObjCCompatibleAliasDecl( ObjCCompatibleAliasDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCContainerDecl( ObjCContainerDecl * v )
{
   cout << endl << "bool VisitObjCContainerDecl( ObjCContainerDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCDictionaryLiteral( ObjCDictionaryLiteral * v )
{
   cout << endl << "bool VisitObjCDictionaryLiteral( ObjCDictionaryLiteral * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCEncodeExpr( ObjCEncodeExpr * v )
{
   cout << endl << "bool VisitObjCEncodeExpr( ObjCEncodeExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCForCollectionStmt( ObjCForCollectionStmt * v )
{
   cout << endl << "bool VisitObjCForCollectionStmt( ObjCForCollectionStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCImplDecl( ObjCImplDecl * v )
{
   cout << endl << "bool VisitObjCImplDecl( ObjCImplDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCImplementationDecl( ObjCImplementationDecl * v )
{
   cout << endl << "bool VisitObjCImplementationDecl( ObjCImplementationDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCIndirectCopyRestoreExpr( ObjCIndirectCopyRestoreExpr * v )
{
   cout << endl << "bool VisitObjCIndirectCopyRestoreExpr( ObjCIndirectCopyRestoreExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCInterfaceDecl( ObjCInterfaceDecl * v )
{
   cout << endl << "bool VisitObjCInterfaceDecl( ObjCInterfaceDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCInterfaceType( ObjCInterfaceType * v )
{
   cout << endl << "bool VisitObjCInterfaceType( ObjCInterfaceType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCIsaExpr( ObjCIsaExpr * v )
{
   cout << endl << "bool VisitObjCIsaExpr( ObjCIsaExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCIvarDecl( ObjCIvarDecl * v )
{
   cout << endl << "bool VisitObjCIvarDecl( ObjCIvarDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCIvarRefExpr( ObjCIvarRefExpr * v )
{
   cout << endl << "bool VisitObjCIvarRefExpr( ObjCIvarRefExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCMessageExpr( ObjCMessageExpr * v )
{
   cout << endl << "bool VisitObjCMessageExpr( ObjCMessageExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCMethodDecl( ObjCMethodDecl * v )
{
   cout << endl << "bool VisitObjCMethodDecl( ObjCMethodDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCObjectPointerType( ObjCObjectPointerType * v )
{
   cout << endl << "bool VisitObjCObjectPointerType( ObjCObjectPointerType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCObjectType( ObjCObjectType * v )
{
   cout << endl << "bool VisitObjCObjectType( ObjCObjectType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCPropertyDecl( ObjCPropertyDecl * v )
{
   cout << endl << "bool VisitObjCPropertyDecl( ObjCPropertyDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCPropertyImplDecl( ObjCPropertyImplDecl * v )
{
   cout << endl << "bool VisitObjCPropertyImplDecl( ObjCPropertyImplDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCPropertyRefExpr( ObjCPropertyRefExpr * v )
{
   cout << endl << "bool VisitObjCPropertyRefExpr( ObjCPropertyRefExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCProtocolDecl( ObjCProtocolDecl * v )
{
   cout << endl << "bool VisitObjCProtocolDecl( ObjCProtocolDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCProtocolExpr( ObjCProtocolExpr * v )
{
   cout << endl << "bool VisitObjCProtocolExpr( ObjCProtocolExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCSelectorExpr( ObjCSelectorExpr * v )
{
   cout << endl << "bool VisitObjCSelectorExpr( ObjCSelectorExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCStringLiteral( ObjCStringLiteral * v )
{
   cout << endl << "bool VisitObjCStringLiteral( ObjCStringLiteral * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitObjCSubscriptRefExpr( ObjCSubscriptRefExpr * v )
{
   cout << endl << "bool VisitObjCSubscriptRefExpr( ObjCSubscriptRefExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitOffsetOfExpr( OffsetOfExpr * v )
{
   cout << endl << "bool VisitOffsetOfExpr( OffsetOfExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitOpaqueValueExpr( OpaqueValueExpr * v )
{
   cout << endl << "bool VisitOpaqueValueExpr( OpaqueValueExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitOverloadExpr( OverloadExpr * v )
{
   cout << endl << "bool VisitOverloadExpr( OverloadExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitPackExpansionExpr( PackExpansionExpr * v )
{
   cout << endl << "bool VisitPackExpansionExpr( PackExpansionExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitPackExpansionType( PackExpansionType * v )
{
   cout << endl << "bool VisitPackExpansionType( PackExpansionType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitParenExpr( ParenExpr * v )
{
   cout << endl << "bool VisitParenExpr( ParenExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitParenListExpr( ParenListExpr * v )
{
   cout << endl << "bool VisitParenListExpr( ParenListExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitParenType( ParenType * v )
{
   cout << endl << "bool VisitParenType( ParenType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitParmVarDecl( ParmVarDecl * v )
{
   cout << endl << "bool VisitParmVarDecl( ParmVarDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitPointerType( PointerType * v )
{
   cout << endl << "bool VisitPointerType( PointerType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitPredefinedExpr( PredefinedExpr * v )
{
   cout << endl << "bool VisitPredefinedExpr( PredefinedExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitPseudoObjectExpr( PseudoObjectExpr * v )
{
   cout << endl << "bool VisitPseudoObjectExpr( PseudoObjectExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitRecordDecl( RecordDecl * v )
{
   cout << endl << "bool VisitRecordDecl( RecordDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitRecordType( RecordType * v )
{
   cout << endl << "bool VisitRecordType( RecordType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitRedeclarableTemplateDecl( RedeclarableTemplateDecl * v )
{
   cout << endl << "bool VisitRedeclarableTemplateDecl( RedeclarableTemplateDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitReferenceType( ReferenceType * v )
{
   cout << endl << "bool VisitReferenceType( ReferenceType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitReturnStmt( ReturnStmt * v )
{
   cout << endl << "bool VisitReturnStmt( ReturnStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitRValueReferenceType( RValueReferenceType * v )
{
   cout << endl << "bool VisitRValueReferenceType( RValueReferenceType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitSEHExceptStmt( SEHExceptStmt * v )
{
   cout << endl << "bool VisitSEHExceptStmt( SEHExceptStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitSEHFinallyStmt( SEHFinallyStmt * v )
{
   cout << endl << "bool VisitSEHFinallyStmt( SEHFinallyStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitSEHTryStmt( SEHTryStmt * v )
{
   cout << endl << "bool VisitSEHTryStmt( SEHTryStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitShuffleVectorExpr( ShuffleVectorExpr * v )
{
   cout << endl << "bool VisitShuffleVectorExpr( ShuffleVectorExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitSizeOfPackExpr( SizeOfPackExpr * v )
{
   cout << endl << "bool VisitSizeOfPackExpr( SizeOfPackExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitStaticAssertDecl( StaticAssertDecl * v )
{
   cout << endl << "bool VisitStaticAssertDecl( StaticAssertDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitStmtExpr( StmtExpr * v )
{
   cout << endl << "bool VisitStmtExpr( StmtExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitStmt( Stmt * v )
{
   cout << endl << "bool VisitStmt( Stmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitStringLiteral( StringLiteral * v )
{
   cout << endl << "bool VisitStringLiteral( StringLiteral * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitSubstNonTypeTemplateParmExpr( SubstNonTypeTemplateParmExpr * v )
{
   cout << endl << "bool VisitSubstNonTypeTemplateParmExpr( SubstNonTypeTemplateParmExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitSubstNonTypeTemplateParmPackExpr( SubstNonTypeTemplateParmPackExpr * v )
{
   cout << endl << "bool VisitSubstNonTypeTemplateParmPackExpr( SubstNonTypeTemplateParmPackExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitSubstTemplateTypeParmPackType( SubstTemplateTypeParmPackType * v )
{
   cout << endl << "bool VisitSubstTemplateTypeParmPackType( SubstTemplateTypeParmPackType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitSubstTemplateTypeParmType( SubstTemplateTypeParmType * v )
{
   cout << endl << "bool VisitSubstTemplateTypeParmType( SubstTemplateTypeParmType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitSwitchCase( SwitchCase * v )
{
   cout << endl << "bool VisitSwitchCase( SwitchCase * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitSwitchStmt( SwitchStmt * v )
{
   cout << endl << "bool VisitSwitchStmt( SwitchStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTagDecl( TagDecl * v )
{
   cout << endl << "bool VisitTagDecl( TagDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTagType( TagType * v )
{
   cout << endl << "bool VisitTagType( TagType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTemplateDecl( TemplateDecl * v )
{
   cout << endl << "bool VisitTemplateDecl( TemplateDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTemplateSpecializationType( TemplateSpecializationType * v )
{
   cout << endl << "bool VisitTemplateSpecializationType( TemplateSpecializationType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTemplateTemplateParmDecl( TemplateTemplateParmDecl * v )
{
   cout << endl << "bool VisitTemplateTemplateParmDecl( TemplateTemplateParmDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTemplateTypeParmDecl( TemplateTypeParmDecl * v )
{
   cout << endl << "bool VisitTemplateTypeParmDecl( TemplateTypeParmDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTemplateTypeParmType( TemplateTypeParmType * v )
{
   cout << endl << "bool VisitTemplateTypeParmType( TemplateTypeParmType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTranslationUnitDecl( TranslationUnitDecl * v )
{
   cout << endl << "bool VisitTranslationUnitDecl( TranslationUnitDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTypeAliasDecl( TypeAliasDecl * v )
{
   cout << endl << "bool VisitTypeAliasDecl( TypeAliasDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTypeAliasTemplateDecl( TypeAliasTemplateDecl * v )
{
   cout << endl << "bool VisitTypeAliasTemplateDecl( TypeAliasTemplateDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTypeDecl( TypeDecl * v )
{
   cout << endl << "bool VisitTypeDecl( TypeDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTypedefNameDecl( TypedefNameDecl * v )
{
   cout << endl << "bool VisitTypedefNameDecl( TypedefNameDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTypedefType( TypedefType * v )
{
   cout << endl << "bool VisitTypedefType( TypedefType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTypeOfExprType( TypeOfExprType * v )
{
   cout << endl << "bool VisitTypeOfExprType( TypeOfExprType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTypeOfType( TypeOfType * v )
{
   cout << endl << "bool VisitTypeOfType( TypeOfType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitTypeTraitExpr( TypeTraitExpr * v )
{
   cout << endl << "bool VisitTypeTraitExpr( TypeTraitExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitType( Type * v )
{
   cout << endl << "bool VisitType( Type * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryAddrOf( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryAddrOf( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryDeref( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryDeref( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryExprOrTypeTraitExpr( UnaryExprOrTypeTraitExpr * v )
{
   cout << endl << "bool VisitUnaryExprOrTypeTraitExpr( UnaryExprOrTypeTraitExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryExtension( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryExtension( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryImag( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryImag( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryLNot( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryLNot( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryMinus( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryMinus( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryNot( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryNot( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryOperator( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryOperator( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryPlus( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryPlus( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryPostDec( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryPostDec( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryPostInc( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryPostInc( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryPreDec( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryPreDec( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryPreInc( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryPreInc( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryReal( UnaryOperator * v )
{
   cout << endl << "bool VisitUnaryReal( UnaryOperator * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryTransformType( UnaryTransformType * v )
{
   cout << endl << "bool VisitUnaryTransformType( UnaryTransformType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnaryTypeTraitExpr( UnaryTypeTraitExpr * v )
{
   cout << endl << "bool VisitUnaryTypeTraitExpr( UnaryTypeTraitExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnresolvedLookupExpr( UnresolvedLookupExpr * v )
{
   cout << endl << "bool VisitUnresolvedLookupExpr( UnresolvedLookupExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnresolvedMemberExpr( UnresolvedMemberExpr * v )
{
   cout << endl << "bool VisitUnresolvedMemberExpr( UnresolvedMemberExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnresolvedUsingTypenameDecl( UnresolvedUsingTypenameDecl * v )
{
   cout << endl << "bool VisitUnresolvedUsingTypenameDecl( UnresolvedUsingTypenameDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnresolvedUsingType( UnresolvedUsingType * v )
{
   cout << endl << "bool VisitUnresolvedUsingType( UnresolvedUsingType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUnresolvedUsingValueDecl( UnresolvedUsingValueDecl * v )
{
   cout << endl << "bool VisitUnresolvedUsingValueDecl( UnresolvedUsingValueDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUserDefinedLiteral( UserDefinedLiteral * v )
{
   cout << endl << "bool VisitUserDefinedLiteral( UserDefinedLiteral * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUsingDecl( UsingDecl * v )
{
   cout << endl << "bool VisitUsingDecl( UsingDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUsingDirectiveDecl( UsingDirectiveDecl * v )
{
   cout << endl << "bool VisitUsingDirectiveDecl( UsingDirectiveDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitUsingShadowDecl( UsingShadowDecl * v )
{
   cout << endl << "bool VisitUsingShadowDecl( UsingShadowDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitVAArgExpr( VAArgExpr * v )
{
   cout << endl << "bool VisitVAArgExpr( VAArgExpr * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitValueDecl( ValueDecl * v )
{
   cout << endl << "bool VisitValueDecl( ValueDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitVarDecl( VarDecl * v )
{
   cout << endl << "bool VisitVarDecl( VarDecl * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitVariableArrayType( VariableArrayType * v )
{
   cout << endl << "bool VisitVariableArrayType( VariableArrayType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitVectorType( VectorType * v )
{
   cout << endl << "bool VisitVectorType( VectorType * v )" << endl ;

   v->dump() ;

   return true ;
}


bool VisitWhileStmt( WhileStmt * v )
{
   cout << endl << "bool VisitWhileStmt( WhileStmt * v )" << endl ;

   v->dump() ;

   return true ;
}


