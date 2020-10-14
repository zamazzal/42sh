/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 23:53:24 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/15 23:53:32 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int	list_error1(void)
{
	if ((errno & E2BIG) == (E2BIG))
		ft_putstr_fd("Liste d'arguments trop longue.", 2);
	else if ((errno & EACCES) == (EACCES))
		ft_putstr_fd("Permission refusée.", 2);
	else if ((errno & EADDRINUSE) == (EADDRINUSE))
		ft_putstr_fd("Adresse déjà en cours d'utilisation.", 2);
	else if ((errno & EADDRNOTAVAIL) == (EADDRNOTAVAIL))
		ft_putstr_fd("Adresse non disponible.", 2);
	else if ((errno & EAFNOSUPPORT) == (EAFNOSUPPORT))
		ft_putstr_fd("Famille d'adresses non supportée.", 2);
	else if ((errno & EAGAIN) == (EAGAIN))
		ft_putstr_fd("Ressource temporairement indisponible.", 2);
	else if ((errno & EALREADY) == EALREADY)
		ft_putstr_fd("Connexion déjà en cours .", 2);
	else if ((errno & EBADF) == (EBADF))
		ft_putstr_fd("Bad file descritor.", 2);
	else if ((errno & EBADMSG) == (EBADMSG))
		ft_putstr_fd("Mauvais message.", 2);
	else if ((errno & EBUSY) == (EBUSY))
		ft_putstr_fd("Ressource ou périphérique occupé.", 2);
	else
		return (0);
	return (1);
}

int	list_error2(void)
{
	if ((errno & ECHILD) == (ECHILD))
		ft_putstr_fd("Pas de processus fils.", 2);
	else if ((errno & ECONNABORTED) == (ECONNABORTED))
		ft_putstr_fd("Connexion abandonnée.", 2);
	else if ((errno & ECHILD) == (ECHILD))
		ft_putstr_fd("Pas de processus fils.", 2);
	else if ((errno & ECONNREFUSED) == (ECONNREFUSED))
		ft_putstr_fd("Connexion refusée.", 2);
	else if ((errno & ECONNRESET) == (ECONNRESET))
		ft_putstr_fd("Connexion réinitialisée.", 2);
	else if ((errno & EDEADLK) == (EDEADLK))
		ft_putstr_fd("Blocage d'une ressource évité.", 2);
	else if ((errno & EDESTADDRREQ) == (EDESTADDRREQ))
		ft_putstr_fd("Adresse de destination nécessaire.", 2);
	else if ((errno & EDQUOT) == (EDQUOT))
		ft_putstr_fd("Quota disque dépassé.", 2);
	else if ((errno & EEXIST) == (EEXIST))
		ft_putstr_fd("Fichier existant.", 2);
	else
		return (0);
	return (1);
}

int	list_error3(void)
{
	if ((errno & EFAULT) == (EFAULT))
		ft_putstr_fd("Mauvaise adresse.", 2);
	else if ((errno & EFBIG) == (EFBIG))
		ft_putstr_fd("Fichier trop grand.", 2);
	else if ((errno & EHOSTDOWN) == (EHOSTDOWN))
		ft_putstr_fd("Hôte éteint.", 2);
	else if ((errno & EHOSTUNREACH) == (EHOSTUNREACH))
		ft_putstr_fd("Hôte non accessible.", 2);
	else if ((errno & EIDRM) == (EIDRM))
		ft_putstr_fd("Identificateur supprimé.", 2);
	else if ((errno & EILSEQ) == (EILSEQ))
		ft_putstr_fd("Séquence d'octets illégale.", 2);
	else if ((errno & EINPROGRESS) == (EINPROGRESS))
		ft_putstr_fd("Opération en cours.", 2);
	else if ((errno & EINTR) == (EINTR))
		ft_putstr_fd("Appel système interrompu.", 2);
	else if ((errno & EINVAL) == (EINVAL))
		ft_putstr_fd("Argument invalide.", 2);
	else if ((errno & EIO) == (EIO))
		ft_putstr_fd("Erreur d'entrée-sortie.", 2);
	else
		return (0);
	return (1);
}

int	list_error4(void)
{
	if ((errno & ECANCELED) == (ECANCELED))
		ft_putstr_fd("Opération annulée.", 2);
	else if ((errno & EISCONN) == (EISCONN))
		ft_putstr_fd("La socket est connectée.", 2);
	else if ((errno & EISDIR) == (EISDIR))
		ft_putstr_fd("Est un répertoire.", 2);
	else if ((errno & ELOOP) == (ELOOP))
		ft_putstr_fd("Trop de niveaux de liens symboliques rencontrés.", 2);
	else if ((errno & EMFILE) == (EMFILE))
		ft_putstr_fd("Trop de fichiers ouverts.", 2);
	else if ((errno & EMLINK) == (EMLINK))
		ft_putstr_fd("Trop de liens symboliques.", 2);
	else if ((errno & EMSGSIZE) == (EMSGSIZE))
		ft_putstr_fd("Message trop long.", 2);
	else if ((errno & EMULTIHOP) == (EMULTIHOP))
		ft_putstr_fd("Tentative de saut multiple « Multihop ».", 2);
	else if ((errno & ENAMETOOLONG) == (ENAMETOOLONG))
		ft_putstr_fd("Nom de fichier trop long.", 2);
	else if ((errno & ENETDOWN) == (ENETDOWN))
		ft_putstr_fd("Le réseau est désactivé.", 2);
	else
		return (0);
	return (1);
}
