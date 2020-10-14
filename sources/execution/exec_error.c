/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:51:41 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 23:53:13 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	list_error5(void)
{
	if ((errno & ENETRESET) == (ENETRESET))
		ft_putstr_fd("Connexion annulée par le réseau.", 2);
	else if ((errno & ENETUNREACH) == (ENETUNREACH))
		ft_putstr_fd("Réseau inaccessible.", 2);
	else if ((errno & ENFILE) == (ENFILE))
		ft_putstr_fd("Trop de fichiers ouverts sur le système.", 2);
	else if ((errno & ENOBUFS) == (ENOBUFS))
		ft_putstr_fd("Plus de tampons disponibles.", 2);
	else if ((errno & ENODATA) == (ENODATA))
		ft_putstr_fd("Pas de message disponible dans la file STREAM.", 2);
	else if ((errno & ENODEV) == (ENODEV))
		ft_putstr_fd("Périphérique inexistant.", 2);
	else if ((errno & ENOENT) == (ENOENT))
		ft_putstr_fd("Fichier ou répertoire inexistant.", 2);
	else if ((errno & ENOEXEC) == (ENOEXEC))
		ft_putstr_fd("Erreur de format d'exécution.", 2);
	else if ((errno & ENOLCK) == (ENOLCK))
		ft_putstr_fd("Pas de verrou disponible .", 2);
	else if ((errno & ENOLINK) == (ENOLINK))
		ft_putstr_fd("Le lien a été coupé.", 2);
	else
		return (0);
	return (1);
}

static int	list_error6(void)
{
	if ((errno & ENOMEM) == (ENOMEM))
		ft_putstr_fd("Pas assez de mémoire.", 2);
	else if ((errno & ENOMSG) == (ENOMSG))
		ft_putstr_fd("Pas de message du type attendu.", 2);
	else if ((errno & ENOPROTOOPT) == (ENOPROTOOPT))
		ft_putstr_fd("Protocole indisponible.", 2);
	else if ((errno & ENOSPC) == (ENOSPC))
		ft_putstr_fd("Plus de place sur le périphérique.", 2);
	else if ((errno & ENOSR) == (ENOSR))
		ft_putstr_fd("Pas de ressource STREAM.", 2);
	else if ((errno & ENOSTR) == (ENOSTR))
		ft_putstr_fd("Pas un STREAM.", 2);
	else if ((errno & ENOSYS) == (ENOSYS))
		ft_putstr_fd("Fonction non implémentée.", 2);
	else if ((errno & ENOTBLK) == (ENOTBLK))
		ft_putstr_fd("Périphérique de bloc requis.", 2);
	else if ((errno & ENOTCONN) == (ENOTCONN))
		ft_putstr_fd("La socket n'est pas connectée.", 2);
	else if ((errno & ENOTDIR) == (ENOTDIR))
		ft_putstr_fd("Pas un répertoire.", 2);
	else if ((errno & ENOTEMPTY) == (ENOTEMPTY))
		ft_putstr_fd("Répertoire non vide.", 2);
	else
		return (0);
	return (1);
}

static int	list_error7(void)
{
	if ((errno & ENOTSOCK) == (ENOTSOCK))
		ft_putstr_fd("Pas une socket.", 2);
	else if ((errno & ENOTSUP) == (ENOTSUP))
		ft_putstr_fd("Opération non supportée.", 2);
	else if ((errno & ENOTTY) == (ENOTTY))
		ft_putstr_fd("Opération de contrôle d'entrée-sortie invalide.", 2);
	else if ((errno & ENXIO) == (ENXIO))
		ft_putstr_fd("Périphérique ou adresse inexistant.", 2);
	else if ((errno & EOPNOTSUPP) == (EOPNOTSUPP))
		ft_putstr_fd("Opération non supportée par la socket.", 2);
	else if ((errno & EPERM) == (EPERM))
		ft_putstr_fd("Opération interdite.", 2);
	else if ((errno & EPFNOSUPPORT) == (EPFNOSUPPORT))
		ft_putstr_fd("Famille de protocole non supportée.", 2);
	else if ((errno & EPIPE) == (EPIPE))
		ft_putstr_fd("Tube brisé.", 2);
	else if ((errno & EPROTO) == (EPROTO))
		ft_putstr_fd("Erreur de protocole.", 2);
	else
		return (0);
	return (1);
}

static int	list_error8(void)
{
	if ((errno & EPROTONOSUPPORT) == (EPROTONOSUPPORT))
		ft_putstr_fd("Protocole non supporté.", 2);
	else if ((errno & EPROTOTYPE) == (EPROTOTYPE))
		ft_putstr_fd("Mauvais type de protocole pour la socket.", 2);
	else if ((errno & ERANGE) == (ERANGE))
		ft_putstr_fd("Résultat trop grand.", 2);
	else if ((errno & EREMOTE) == (EREMOTE))
		ft_putstr_fd("L'objet est distant.", 2);
	else if ((errno & EROFS) == (EROFS))
		ft_putstr_fd("Système de fichiers en lecture seule.", 2);
	else if ((errno & ESPIPE) == (ESPIPE))
		ft_putstr_fd("Recherche invalide.", 2);
	else if ((errno & ESOCKTNOSUPPORT) == (ESOCKTNOSUPPORT))
		ft_putstr_fd("Type de socket non supporté.", 2);
	else if ((errno & ESRCH) == (ESRCH))
		ft_putstr_fd("Processus inexistant.", 2);
	else
		return (0);
	return (1);
}

int			ft_perror(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	if ((errno & ESTALE) == (ESTALE))
		ft_putstr_fd("Descripteur de fichier éventé", 2);
	if ((errno & ETIME) == (ETIME))
		ft_putstr_fd("Temporisation expirée.", 2);
	else if ((errno & ETIMEDOUT) == (ETIMEDOUT))
		ft_putstr_fd("Délai maximal de connexion écoulé.", 2);
	else if ((errno & ETXTBSY) == (ETXTBSY))
		ft_putstr_fd("Fichier texte occupé.", 2);
	else if ((errno & EUSERS) == (EUSERS))
		ft_putstr_fd("Trop d'utilisateurs.", 2);
	else if ((errno & EWOULDBLOCK) == (EWOULDBLOCK))
		ft_putstr_fd("L'opération serait bloquante.", 2);
	else if ((errno & EXDEV) == (EXDEV))
		ft_putstr_fd("Lien inapproprié.", 2);
	else if (!list_error1() && !list_error2() && !list_error3()
	&& !list_error4() && !list_error5()
	&& !list_error6() && !list_error7() && !list_error8())
		ft_putstr_fd("indefiend error.", 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}
